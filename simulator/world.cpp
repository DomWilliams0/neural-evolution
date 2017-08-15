#include "world.h"
#include "config.h"

World::World(b2Vec2 dims) : dims(dims), time(0), physWorld({0.0, 0.0}) {

}

void World::tick(float dt) {
    // tick time
    time += dt;
    time = static_cast<int>(time) % Config::TIME_GRANUALITY;

    // TODO depends on fast forward or not
    physWorld.Step(dt, 2, 2);
}

float World::getTime() const {
    return time * Config::TIME_GRANUALITY_RECIP;
}

float World::getTemperature(const b2Vec2 &pos) const {
    // TODO noise
    return 0;
}

b2Vec2 World::getDimensions() const {
    return dims;
}
