#ifndef NEURAL_EVOLUTION_COLLISION_H
#define NEURAL_EVOLUTION_COLLISION_H

#include <entityx/Entity.h>
#include "component.h"

enum EntityType {
    ENTITY = 1 << 0,
    FOOD = 1 << 1
};

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
};


#endif