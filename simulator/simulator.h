#ifndef NEURAL_EVOLUTION_SIMULATOR_H
#define NEURAL_EVOLUTION_SIMULATOR_H

#include <entityx/entityx.h>
#include <Box2D/Box2D.h>

#include "config.h"
#include "component.h"
#include "world.h"

struct EntityDef {
    EntityDef(const entityx::Entity &id, const b2Vec2 &pos, World *world, float radius = Config::ENTITY_RADIUS,
              NeuralNetwork *brain = nullptr) : id(id),
                                                pos(pos),
                                                world(world),
                                                radius(radius),
                                                brain(brain) {}

    entityx::Entity id;
    b2Vec2 pos;
    World *world;
    float radius;
    NeuralNetwork *brain;
};

class Simulator : public entityx::EntityX {

protected:
    World world;

    float generationTime;
    unsigned int generationNumber;
    float timeScale;

    std::vector<EntityDef> queuedSpawns;

    void startNewGeneration();

    void createEntitiesFromBrains(std::vector<EntityDef> &out, const std::vector<NeuralNetwork *> &brains);

    void spawnEntities(const std::vector<EntityDef> &defs);

public:
    Simulator();

    void tick(float dt);

    b2World &getPhysicsWorld();

    unsigned int getGenerationNumber() const;

    void setTimeScale(float scale);

};


#endif
