#include <vector>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include "simulator.h"

void initLogger() {
    static plog::ColorConsoleAppender<plog::TxtFormatter> appender;
    plog::init(plog::debug, &appender);
}


Simulator::Simulator() : world({Config::WORLD_WIDTH, Config::WORLD_HEIGHT}),
                         generationTime(Config::TIME_PER_GENERATION),
                         generationNumber(0) {
    initLogger();

    // TODO register systems
    systems.configure();

    // create first generation from nothing
    std::vector<EntityDef> firstGeneration;
    createEntitiesFromBrains(firstGeneration, {});
    spawnEntities(firstGeneration);

}

void Simulator::tick(double dt) {

    generationTime -= dt;

    if (generationTime < 0)
        startNewGeneration();

    // populate new entities
    for (EntityDef &def : queuedSpawns) {
        def.id.assign<Brain>();

        // physics
        b2Body *body = nullptr;
        b2Fixture *fixture = nullptr;
        def.world->spawnEntity(def.pos, def.radius, &body, &fixture);
        def.id.assign<Physics>(body, fixture, def.radius);
        LOGD << "Spawning new entity at (" << def.pos.x << ", " << def.pos.y << ")";
    }
    queuedSpawns.clear();

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
    std::vector<Brain *> mutatedBrains;
    // TODO copy, mutate and delete old fit brains

    std::vector<EntityDef> newGeneration;
    createEntitiesFromBrains(newGeneration, mutatedBrains);
    spawnEntities(newGeneration);
}

void Simulator::createEntitiesFromBrains(std::vector<EntityDef> &out, const std::vector<Brain *> &brains) {
    // TODO cycle through brains and create

    EntityDef test(entities.create(), {100, 100}, &world);
    out.push_back(test);
}

void Simulator::spawnEntities(const std::vector<EntityDef> &defs) {
    // on start of next tick
    queuedSpawns.insert(queuedSpawns.end(), defs.cbegin(), defs.cend());
}
