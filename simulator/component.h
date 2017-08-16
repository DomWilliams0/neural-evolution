#ifndef NEURAL_EVOLUTION_COMPONENT_H
#define NEURAL_EVOLUTION_COMPONENT_H

#include <Box2D/Box2D.h>

class World;

class NeuralNetwork;

struct Physics {
    Physics(b2Body *body, b2Fixture *fixture, float radius) : body(body), fixture(fixture), radius(radius) {}

    inline b2Vec2 getPosition() const { return body->GetPosition(); }

    b2Body *body;
    b2Fixture *fixture;
    float radius;
};

struct Brain {
    Brain(NeuralNetwork *network) : network(network) {}

    NeuralNetwork *network;
};

struct Nutrition {
    int nutrition;

    Nutrition(int nutrition) : nutrition(nutrition) {}
};


#endif
