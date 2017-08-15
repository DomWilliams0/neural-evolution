#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include "simulator.h"
#include "config.h"

void initLogger() {
    plog::init(plog::debug);
}


Simulator::Simulator() : physicsWorld({Config::WORLD_WIDTH, Config::WORLD_HEIGHT}), generationTime(0.f),
                         generationNumber(0.f) {
    initLogger();

    // register systems
}

void Simulator::tick(double dt) {

    generationTime -= dt;

    if (generationTime < 0)
        startNewGeneration();

    systems.update_all(dt);
}

void Simulator::startNewGeneration() {
    // reset clock
    generationTime = Config::TIME_PER_GENERATION;

    generationNumber += 1;

    LOG_INFO << "New generation " << generationNumber;

    // collect fittest brains
    // reset the world
    // mutate and add back to world
}
