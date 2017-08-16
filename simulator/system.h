#ifndef NEURAL_EVOLUTION_SYSTEM_H
#define NEURAL_EVOLUTION_SYSTEM_H

#include <entityx/System.h>

struct BrainSystem : public entityx::System<BrainSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

struct NutritionSystem : public entityx::System<NutritionSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

#endif