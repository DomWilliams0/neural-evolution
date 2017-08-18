#include <util.h>
#include "renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, Simulator &sim) :
        window(sf::VideoMode(width, height), "Neural Evolution", sf::Style::None),
        sim(sim), debugRenderer(window), currentGeneration(0) {

    debugRenderer.AppendFlags(b2Draw::e_shapeBit);
    sim.getWorld().getPhysicsWorld().SetDebugDraw(&debugRenderer);

    if (!font.loadFromFile("renderer/font.ttf"))
        throw std::runtime_error("Missing font.ttf");

    generationLabel.setFont(font);
    generationLabel.setFillColor(sf::Color::White);

    // sets renderer
    setFastForward(false);
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
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                        setFastForward(!fastForward);
                    else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)
                        window.close();

                default:
                    break;
            }
        }

        sf::Color clear(85, 98, 100);
        window.clear(clear);

        float dt(clock.restart().asSeconds());
        tick(dt);
        (this->*renderer)();

        window.display();
    }
}

static sf::Vector2f vec(const b2Vec2 &b2) {
    return {b2.x, b2.y};
}


void Renderer::setFastForward(bool ff) {
    fastForward = ff;
    if (fastForward) {
        renderer = &Renderer::renderFastForward;
        generationLabel.setCharacterSize(Config::FONT_SIZE_FAST_FORWARD);
        sf::Vector2f pos(window.getSize().x / 2, window.getSize().y / 2);
        sf::FloatRect bounds(generationLabel.getLocalBounds());
        pos.x -= bounds.width / 2;
        pos.y -= bounds.height / 2;
        generationLabel.setPosition(pos);
    } else {
        renderer = &Renderer::renderSimulation;
        generationLabel.setCharacterSize(Config::FONT_SIZE_NORMAL_SPEED);
        generationLabel.setPosition(5, Config::WORLD_HEIGHT - Config::FONT_SIZE_NORMAL_SPEED - 5);
    }
}

void Renderer::tick(float dt) {
    sim.tick(fastForward ? Config::FAST_FORWARD_TIME_SCALE : dt);

    unsigned int current = sim.getGenerationNumber();
    if (current != currentGeneration) {
        currentGeneration = current;
        generationLabel.setString("Generation " + std::to_string(current));
    }
}

void Renderer::renderSimulation() {
    sf::Color foodColour(154, 185, 153);
    const b2Fixture *food = sim.getWorld().listFood();
    while (food != nullptr) {
        b2CircleShape *foodCircle = (b2CircleShape *) food->GetShape();
        sf::CircleShape circle(foodCircle->m_radius, 30);
        circle.setFillColor(foodColour);
        circle.setOutlineColor({0, 0, 0});
        circle.setOutlineThickness(1);
        circle.setPosition({foodCircle->m_p.x - foodCircle->m_radius, foodCircle->m_p.y - foodCircle->m_radius});
        window.draw(circle);
        food = food->GetNext();
    }


    sim.entities.each<Physics, FoodSensor>([this](entityx::Entity entity, Physics &physics, FoodSensor &sensor) {
        sf::Color bodyColour(231, 219, 151);
        sf::Color velocityColour(231, 219, 151);
        sf::Color sensorColourOff(39, 54, 59);
        sf::Color sensorColourOn(235, 73, 96);

        b2Vec2 pos(physics.getPosition());
        b2Vec2 vel(physics.getVelocity());

        pos.x -= physics.radius;
        pos.y -= physics.radius;

        // velocity
        sf::Vertex velocity[2] = {
                sf::Vertex({pos.x + physics.radius, pos.y + physics.radius}, velocityColour),
                sf::Vertex({pos.x + physics.radius + vel.x, pos.y + physics.radius + vel.y}, velocityColour),
        };
        window.draw(velocity, 2, sf::Lines);

        // body
        sf::CircleShape circle(physics.radius, 30);
        circle.setFillColor(bodyColour);
        circle.setOutlineColor({0, 0, 0});
        circle.setOutlineThickness(1);
        circle.setPosition(vec(pos));
        window.draw(circle);

        // sensor
        VecPair sensorRelativeVertices(
                calculateSensorVertices(sensor.angle + physics.getAngle(), sensor.length, physics.radius));
        sf::Color &sensorColour = sensor.activated() ? sensorColourOn : sensorColourOff;
        sf::Vertex sensorVertices[2] = {
                sf::Vertex({sensorRelativeVertices.first.x + pos.x + physics.radius,
                            sensorRelativeVertices.first.y + pos.y + physics.radius}, sensorColour),
                sf::Vertex({sensorRelativeVertices.second.x + pos.x + physics.radius,
                            sensorRelativeVertices.second.y + pos.y + physics.radius}, sensorColour)
        };
        window.draw(sensorVertices, 2, sf::Lines);

    });

    window.draw(generationLabel);

//    sim.getWorld().getPhysicsWorld().DrawDebugData();
}

void Renderer::renderFastForward() {
    window.draw(generationLabel);
}
