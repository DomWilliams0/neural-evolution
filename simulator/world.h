#ifndef NEURAL_EVOLUTION_WORLD_H
#define NEURAL_EVOLUTION_WORLD_H

#include <Box2D/Box2D.h>
#include "entityx/Entity.h"

namespace noise {
    namespace module {
        class Perlin;
    }
}

class CollisionHandler;

class World {

protected:
    b2Vec2 dims;
    float time;

    double temperatureNoiseSeed;
    noise::module::Perlin *temperatureNoise;

    b2World physWorld;
    b2Body *foodFrame;
    CollisionHandler *collisions;

public:
    World();

    void tick(float dt);

    float getTime() const;

    float getTemperature(const b2Vec2 &pos) const;

    b2Vec2 getDimensions() const;

    void spawnEntity(const b2Vec2 &pos, float radius, b2Body **bodyOut, b2Fixture **fixtureOut);

    b2Fixture *spawnFood(const b2Vec2 &pos, float radius);

    b2World &getPhysicsWorld();

    virtual ~World();

    void reset();
};


#endif
