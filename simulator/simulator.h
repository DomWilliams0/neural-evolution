#ifndef NEURAL_EVOLUTION_SIMULATOR_H
#define NEURAL_EVOLUTION_SIMULATOR_H

#include <entityx/entityx.h>
#include <Box2D/Box2D.h>

class Simulator : public entityx::EntityX{

protected:
    b2World physicsWorld;

    float generationTime;
    float generationNumber;

    void startNewGeneration();

public:
    Simulator();

    void tick(double dt);
};


#endif
