#ifndef NEURAL_EVOLUTION_RENDERER_H
#define NEURAL_EVOLUTION_RENDERER_H

#include <SFML/Graphics.hpp>
#include "simulator.h"

class Renderer {
protected:
    sf::RenderWindow window;
    sf::Text generationLabel;

    Simulator &sim;

    void tickAndRender(float dt);

    void tick(float dt);

    void renderSimulation();

public:
    Renderer(unsigned int width, unsigned int height, Simulator &sim);

    void run();

};

#endif