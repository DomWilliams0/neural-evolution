#ifndef NEURAL_EVOLUTION_COLLISION_H
#define NEURAL_EVOLUTION_COLLISION_H

#include <entityx/Entity.h>
#include "component.h"

struct UserData {
    UserData(EntityType type) : type(type) {}

    EntityType type;
    union {
        entityx::Entity entity;
        Nutrition nutrition;
    };
};

class CollisionHandler : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;
};


#endif