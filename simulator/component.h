#ifndef NEURAL_EVOLUTION_COMPONENT_H
#define NEURAL_EVOLUTION_COMPONENT_H

#include <Box2D/Box2D.h>

class World;

struct Physics {
    Physics(b2Body *body, b2Fixture *fixture, float radius) : body(body), fixture(fixture), radius(radius) {}

    b2Body *body;
    b2Fixture *fixture;
    float radius;
};

struct Brain {
    // TODO pointer neural net
};

struct Nutrition {
    int nutrition;

    Nutrition(int nutrition) : nutrition(nutrition) {}
};


#endif
