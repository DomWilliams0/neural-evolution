#include <vector>
#include <noise/noise.h>

#include "world.h"
#include "config.h"


World::World(b2Vec2 dims) : dims(dims), time(0), physWorld({0.0, 0.0}), temperatureNoiseSeed(rand() * dims.x * dims.y),
                            temperatureNoise(new noise::module::Perlin) {
    temperatureNoise->SetFrequency(Config::TEMPERATURE_SCALE);
    temperatureNoise->SetOctaveCount(2);

    b2BodyDef frameDef;
    frameDef.type = b2_staticBody;
    foodFrame = physWorld.CreateBody(&frameDef);
}

World::~World() {
    delete temperatureNoise;
}

void World::tick(float dt) {
    // tick time
    time = static_cast<float>(fmod(time + dt, Config::TIME_GRANUALITY));

    physWorld.Step(dt, 2, 2);
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

void World::spawnEntity(const b2Vec2 &pos, float radius, b2Body **bodyOut, b2Fixture **fixtureOut) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = pos;
    // TODO userdata on body or fixture?

    b2CircleShape circle;
    circle.m_p.SetZero(); // relative to body
    circle.m_radius = static_cast<float32>(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;

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
