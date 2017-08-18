#ifndef NEURAL_EVOLUTION_RENDERER_H
#define NEURAL_EVOLUTION_RENDERER_H

#include <SFML/Graphics.hpp>
#include "simulator.h"
#include "physics_renderer.h"

class Renderer {
protected:
    sf::RenderWindow window;
    PhysicsRenderer debugRenderer;

    Simulator &sim;
    bool fastForward;

    void (Renderer::*renderer)();

    sf::Font font;
    sf::Text generationLabel;
    unsigned int currentGeneration;

    void setFastForward(bool ff);

    void tick(float dt);

    void renderFastForward();

    void renderSimulation();

public:
    Renderer(unsigned int width, unsigned int height, Simulator &sim);

    void run();

};

#endif
