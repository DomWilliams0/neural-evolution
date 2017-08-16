#include "renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, Simulator &sim) :
        window(sf::VideoMode(width, height), "Neural Evolution", sf::Style::None),
        sim(sim) {}

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
    // TODO check generation number and update label
}

void Renderer::renderSimulation() {
    sim.entities.each<Physics>([this](entityx::Entity entity, Physics &physics) {
        sf::CircleShape circle(physics.radius, 10);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(vec(physics.getPosition()));

        window.draw(circle);
    });
}

