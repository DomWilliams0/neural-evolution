#ifndef NEURAL_EVOLUTION_WORLD_H
#define NEURAL_EVOLUTION_WORLD_H

#include <Box2D/Box2D.h>

namespace noise {
    namespace module {
        class Perlin;
    }
}

class World {

protected:
    b2Vec2 dims;
    float time;

    double temperatureNoiseSeed;
    noise::module::Perlin *temperatureNoise;

    b2World physWorld;

public:
    World(b2Vec2 dims);

    void tick(float dt);

    float getTime() const;

    float getTemperature(const b2Vec2 &pos) const;

    b2Vec2 getDimensions() const;

    void spawnEntity(const b2Vec2 &pos, float radius, b2Body **bodyOut, b2Fixture **fixtureOut);

    b2World &getPhysicsWorld();

    virtual ~World();
};


#endif
