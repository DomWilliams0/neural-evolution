
#include <noise/noise.h>
#include <plog/Log.h>

#include "collision.h"
#include "world.h"
#include "config.h"
#include "event.h"
#include "component.h"


World::World() : dims(dims), time(0), physWorld({0.0, 0.0}), temperatureNoiseSeed(rand() * dims.x * dims.y),
                 temperatureNoise(new noise::module::Perlin), collisions(new CollisionHandler()) {
    temperatureNoise->SetFrequency(Config::TEMPERATURE_SCALE);
    temperatureNoise->SetOctaveCount(2);

    b2BodyDef frameDef;
    frameDef.type = b2_staticBody;
    foodFrame = physWorld.CreateBody(&frameDef);

    physWorld.SetContactListener(collisions);
}

World::~World() {
    delete temperatureNoise;

    physWorld.SetContactListener(nullptr);
//    delete collisions;
}

void World::tick(float dt) {
    // tick time
    time = static_cast<float>(fmod(time + dt, Config::TIME_GRANUALITY));

    physWorld.Step(dt, 2, 2);

    // remove all eaten food
    b2Fixture *f = foodFrame->GetFixtureList();
    while (f != nullptr) {
        b2Fixture *next = f->GetNext();
        if (!((UserData *) f->GetUserData())->nutrition.edible) {
            foodFrame->DestroyFixture(f);
        }
        f = next;
    }
}

float World::getTime() const {
    return time * Config::TIME_GRANUALITY_RECIP;
}

float World::getTemperature(const b2Vec2 &pos) const {
    return static_cast<float>(temperatureNoise->GetValue(pos.x, pos.y, temperatureNoiseSeed));
}

b2Vec2 World::getDimensions() const {
    return dims;
}

// helpers
static UserData *createEntityData() {
    return new UserData(EntityType::ENTITY);
}

static UserData *createFoodData() {
    return new UserData(EntityType::FOOD);
}

void World::spawnEntity(const b2Vec2 &pos, float radius, b2Body **bodyOut, b2Fixture **fixtureOut) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = pos;
    bodyDef.bullet = true;

    b2CircleShape circle;
    circle.m_p.SetZero(); // relative to body
    circle.m_radius = static_cast<float32>(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.userData = createEntityData();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
    fixtureDef.shape = &circle;
#pragma clang diagnostic pop

    *bodyOut = physWorld.CreateBody(&bodyDef);
    *fixtureOut = (*bodyOut)->CreateFixture(&fixtureDef);
}


b2Fixture *World::spawnFood(const b2Vec2 &pos, float radius) {
    b2CircleShape circle;
    circle.m_p.Set(pos.x, pos.y);
    circle.m_radius = static_cast<float32>(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.userData = createFoodData();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
    fixtureDef.shape = &circle;
#pragma clang diagnostic pop

    return foodFrame->CreateFixture(&fixtureDef);
}

b2World &World::getPhysicsWorld() {
    return physWorld;
}

void World::reset() {
    // remove all dynamic bodies
    b2Body *b = physWorld.GetBodyList();
    while (b != nullptr) {
        b2Body *next = b->GetNext();
        if (b->GetType() == b2_dynamicBody) {
            physWorld.DestroyBody(b);
        }
        b = next;
    }

    // remove all food
    b2Fixture *f = foodFrame->GetFixtureList();
    while (f != nullptr) {
        b2Fixture *next = f->GetNext();
        foodFrame->DestroyFixture(f);
        f = next;
    }

    time = 0;
}

const b2Fixture *World::listFood() const {
    return foodFrame->GetFixtureList();
}

static const int ENTITY_AND_FOOD = EntityType::ENTITY | EntityType::FOOD;
static const int SENSOR_AND_FOOD = EntityType::FOOD_SENSOR | EntityType::FOOD;

void CollisionHandler::BeginContact(b2Contact *contact) {
    UserData *a = static_cast<UserData *>(contact->GetFixtureA()->GetUserData());
    UserData *b = static_cast<UserData *>(contact->GetFixtureB()->GetUserData());
    int collision = a->type | b->type;
    // TODO filter collisions

    if (collision == ENTITY_AND_FOOD) {
        entityx::Entity e(a->type == EntityType::ENTITY ? a->entity : b->entity);
        Nutrition &n(a->type == EntityType::FOOD ? a->nutrition : b->nutrition);
        Consumer &c(*e.component<Consumer>());

        emit<EatEvent>(c, n);
    }

    else if (collision == SENSOR_AND_FOOD) {
        entityx::Entity e(a->type == EntityType::FOOD_SENSOR ? a->entity : b->entity);
        emit<FoodSenseEvent>(*e.component<FoodSensor>(), true);
    }
}

void CollisionHandler::EndContact(b2Contact *contact) {
    UserData *a = static_cast<UserData *>(contact->GetFixtureA()->GetUserData());
    UserData *b = static_cast<UserData *>(contact->GetFixtureB()->GetUserData());
    int collision = a->type | b->type;

    if (collision == SENSOR_AND_FOOD) {
        entityx::Entity e(a->type == EntityType::FOOD_SENSOR ? a->entity : b->entity);
        emit<FoodSenseEvent>(*e.component<FoodSensor>(), false);
    }
}
