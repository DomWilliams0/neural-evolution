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
        sf::Color bodyColour(50, 40, 180);
        sf::Color velocityColour(250, 250, 255);

        b2Vec2 pos(physics.getPosition());
        b2Vec2 vel(physics.getVelocity());

        // body
        sf::CircleShape circle(physics.radius, 10);
        circle.setFillColor(bodyColour);
        circle.setPosition(vec(pos));
        window.draw(circle);

        // centre
        // velocity
        sf::Vertex velocity[2] = {
                sf::Vertex({pos.x + physics.radius, pos.y + physics.radius}, velocityColour),
                sf::Vertex({pos.x + vel.x + physics.radius, pos.y + vel.y + physics.radius}, velocityColour),
        };
        window.draw(velocity, 2, sf::Lines);

    });
}

