#include "renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, Simulator &sim) :
        window(sf::VideoMode(width, height), "Neural Evolution", sf::Style::None),
        sim(sim), debugRenderer(window), currentGeneration(0) {

    debugRenderer.AppendFlags(b2Draw::e_shapeBit);
    sim.getPhysicsWorld().SetDebugDraw(&debugRenderer);

    if (!font.loadFromFile("renderer/font.ttf"))
        throw std::runtime_error("Missing font.ttf");

    generationLabel.setFont(font);
    generationLabel.setFillColor(sf::Color::White);

    unsigned int fontSize = 15;
    unsigned int padding = 5;
    generationLabel.setPosition(padding, Config::WORLD_HEIGHT - fontSize - padding);
    generationLabel.setCharacterSize(fontSize);
}

void Renderer::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();

        float dt(clock.restart().asSeconds());
        tickAndRender(dt);

        window.display();
    }
}

static sf::Vector2f vec(const b2Vec2 &b2) {
    return {b2.x, b2.y};
}

void Renderer::tickAndRender(float dt) {
    tick(dt);
    renderSimulation();
}

void Renderer::tick(float dt) {
    sim.tick(dt);

    unsigned int current = sim.getGenerationNumber();
    if (current != currentGeneration) {
        currentGeneration = current;
        generationLabel.setString("Generation " + std::to_string(current));
    }
}

void Renderer::renderSimulation() {
    sim.getPhysicsWorld().DrawDebugData();

    sim.entities.each<Physics>([this](entityx::Entity entity, Physics &physics) {
        sf::Color bodyColour(50, 40, 180);
        sf::Color velocityColour(250, 250, 255);

        b2Vec2 pos(physics.getPosition());
        b2Vec2 vel(physics.getVelocity());

        pos.x -= physics.radius;
        pos.y -= physics.radius;

        // body
        sf::CircleShape circle(physics.radius, 10);
        circle.setFillColor(bodyColour);
        circle.setPosition(vec(pos));
        window.draw(circle);

        // velocity
        sf::Vertex velocity[2] = {
                sf::Vertex({pos.x + physics.radius, pos.y + physics.radius}, velocityColour),
                sf::Vertex({pos.x + physics.radius + vel.x, pos.y + physics.radius + vel.y}, velocityColour),
        };
        window.draw(velocity, 2, sf::Lines);

    });

    window.draw(generationLabel);
}

inline sf::Color convertColour(const b2Color &c) {
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
