#include <vector>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include "simulator.h"
#include "system.h"
#include "neural.h"

void initLogger() {
    static plog::ColorConsoleAppender<plog::TxtFormatter> appender;
    plog::init(plog::debug, &appender);
}


Simulator::Simulator() : world({Config::WORLD_WIDTH, Config::WORLD_HEIGHT}),
                         generationTime(Config::TIME_PER_GENERATION),
                         generationNumber(0) {
    initLogger();

    // seed random for OpenNN
    srand(time(NULL));

    // register systems
    systems.add<BrainSystem>(&this->world);
    systems.add<NutritionSystem>();

    systems.configure();

    // create first generation from nothing
    std::vector<EntityDef> firstGeneration;
    createEntitiesFromBrains(firstGeneration, {});
    spawnEntities(firstGeneration);

}

void Simulator::tick(float dt) {

    generationTime -= dt;

    if (generationTime < 0)
        startNewGeneration();

    // populate new entities
    for (EntityDef &def : queuedSpawns) {
        def.id.assign<Brain>(def.brain ? def.brain : new NeuralNetwork);

        // physics
        b2Body *body = nullptr;
        b2Fixture *fixture = nullptr;
        def.world->spawnEntity(def.pos, def.radius, &body, &fixture);
        def.id.assign<Physics>(body, fixture, def.radius);
        LOGD << "Spawning new entity at (" << def.pos.x << ", " << def.pos.y << ")";
    }
    queuedSpawns.clear();

    world.tick(dt);
    systems.update_all(dt);
}

void Simulator::startNewGeneration() {
    // reset clock
    generationTime = Config::TIME_PER_GENERATION;

    generationNumber += 1;

    LOG_INFO << "New generation " << generationNumber;

    // collect fittest brains
    // TODO pointer should be to the neural net, NOT the brain component
    std::vector<Brain *> fittestBrains;
    // TODO sort and collect

    // reset the world

    // mutate and add back to world
    std::vector<NeuralNetwork *> mutatedBrains;
    // TODO copy, mutate and delete old fit brains

    std::vector<EntityDef> newGeneration;
    createEntitiesFromBrains(newGeneration, mutatedBrains);
    spawnEntities(newGeneration);
}

void Simulator::createEntitiesFromBrains(std::vector<EntityDef> &out, const std::vector<NeuralNetwork *> &brains) {
    // TODO cycle through brains and create

    for (int i = 0; i < 20; ++i)
        out.emplace_back(entities.create(), b2Vec2(100 + i * Config::ENTITY_RADIUS * 2, 100), &world,
                         Config::ENTITY_RADIUS, new NeuralNetwork);
}

void Simulator::spawnEntities(const std::vector<EntityDef> &defs) {
    // on start of next tick
    queuedSpawns.insert(queuedSpawns.end(), defs.cbegin(), defs.cend());
}

b2World &Simulator::getPhysicsWorld() {
    return world.getPhysicsWorld();
}
