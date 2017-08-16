#ifndef NEURAL_EVOLUTION_SYSTEM_H
#define NEURAL_EVOLUTION_SYSTEM_H

#include <entityx/System.h>

struct PhysicsSystem : public entityx::System<PhysicsSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

struct BrainSystem : public entityx::System<PhysicsSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

struct NutritionSystem : public entityx::System<PhysicsSystem> {
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

#endif