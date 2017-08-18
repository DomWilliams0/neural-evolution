#include <SFML/Graphics/CircleShape.hpp>
#include "physics_renderer.h"


inline static sf::Color convertColour(const b2Color &c) {
    return sf::Color(static_cast<sf::Uint8>(c.r * 255),
                     static_cast<sf::Uint8>(c.g * 255),
                     static_cast<sf::Uint8>(c.b * 255));
}

void PhysicsRenderer::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
    sf::CircleShape c(radius);
    c.setFillColor(convertColour(color));
    c.setPosition(center.x - radius, center.y - radius);
    window.draw(c);
}

void PhysicsRenderer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    sf::Vertex line[2] = {
            sf::Vertex({p1.x, p1.y}, convertColour(color)),
            sf::Vertex({p2.x, p2.y}, convertColour(color)),
    };
    window.draw(line, 2, sf::Lines);
}

void PhysicsRenderer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {}

void PhysicsRenderer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {}

void PhysicsRenderer::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {}

void PhysicsRenderer::DrawTransform(const b2Transform &xf) {}

PhysicsRenderer::PhysicsRenderer(sf::RenderWindow &window) : window(window) {}
