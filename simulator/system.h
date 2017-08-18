#ifndef NEURAL_EVOLUTION_SYSTEM_H
#define NEURAL_EVOLUTION_SYSTEM_H

#include <entityx/System.h>
#include "world.h"

struct BrainSystem : public entityx::System<BrainSystem> {
    BrainSystem(World *world) : world(world) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

protected:
    World *world;
};

struct NutritionSystem : public entityx::System<NutritionSystem> {
    NutritionSystem(World *world) : world(world), foodTime(0) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

    void reset();

protected:
    float foodTime;
    World *world;

    void spawnRandomFood();
};

#endif