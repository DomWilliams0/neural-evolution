#ifndef NEURAL_EVOLUTION_SYSTEM_H
#define NEURAL_EVOLUTION_SYSTEM_H

#include <entityx/System.h>
#include "world.h"

struct BrainSystem : public entityx::System<BrainSystem> {
protected:
    World *world;
public:
    BrainSystem(World *world) : world(world) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

struct NutritionSystem : public entityx::System<NutritionSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

#endif