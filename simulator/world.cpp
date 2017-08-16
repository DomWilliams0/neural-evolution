#include <vector>
#include <noise/noise.h>

#include "world.h"
#include "config.h"


World::World(b2Vec2 dims) : dims(dims), time(0), physWorld({0.0, 0.0}), temperatureNoiseSeed(rand()),
                            temperatureNoise(new noise::module::Perlin) {
    temperatureNoise->SetFrequency(Config::TEMPERATURE_SCALE);
    temperatureNoise->SetOctaveCount(2);
}

World::~World() {
    delete temperatureNoise;
}

void World::tick(float dt) {
    // tick time
    time = static_cast<float>(fmod(time + dt, Config::TIME_GRANUALITY));

    // TODO depends on fast forward or not
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

b2World &World::getPhysicsWorld() {
    return physWorld;
}
