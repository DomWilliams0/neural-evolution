#ifndef NEURAL_EVOLUTION_RENDERER_H
#define NEURAL_EVOLUTION_RENDERER_H

#include <SFML/Graphics.hpp>
#include "simulator.h"

class PhysicsRenderer : public b2Draw {
protected:
    sf::RenderWindow &window;
public:
    PhysicsRenderer(sf::RenderWindow &window);

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;

    void DrawTransform(const b2Transform &xf) override;
};

#endif

class Renderer {
protected:
    sf::RenderWindow window;
    PhysicsRenderer debugRenderer;

    Simulator &sim;

    sf::Font font;
    sf::Text generationLabel;
    unsigned int currentGeneration;

    void tickAndRender(float dt);

    void tick(float dt);

    void renderSimulation();

public:
    Renderer(unsigned int width, unsigned int height, Simulator &sim);

    void run();

};
