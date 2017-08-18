#ifndef NEURAL_EVOLUTION_COMPONENT_H
#define NEURAL_EVOLUTION_COMPONENT_H

#include <Box2D/Box2D.h>

class World;

class NeuralNetwork;

struct Physics {
    Physics(b2Body *body, b2Fixture *fixture, float radius) : body(body), fixture(fixture), radius(radius) {}

    inline b2Vec2 getPosition() const { return body->GetPosition(); }

    inline b2Vec2 getVelocity() const { return body->GetLinearVelocity(); }

    b2Body *body;
    b2Fixture *fixture;
    float radius;
};

struct Brain {
    Brain(NeuralNetwork *network) : network(network) {}

    NeuralNetwork *network;
};

struct Nutrition {
    float nutrition;
    bool edible;

    Nutrition(float nutrition) : nutrition(nutrition), edible(true) {}
    Nutrition() : Nutrition(0) {}
};

struct Consumer {
    float totalEaten;

    Consumer() : totalEaten(0) {}
};

#endif
