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
                         generationNumber(1) {
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
    }
    queuedSpawns.clear();

    world.tick(dt);
    systems.update_all(dt);
}

// arbitrarily distance to 400, 400
float fitnessFunction(entityx::Entity &entity) {
    b2Vec2 target(400, 400);
    b2Vec2 current(entity.component<Physics>()->getPosition());

    return (target - current).LengthSquared();
}

void Simulator::startNewGeneration() {
    // reset clock
    generationTime = Config::TIME_PER_GENERATION;

    generationNumber += 1;

    LOG_INFO << "New generation " << generationNumber;

    typedef std::pair<entityx::Entity, NeuralNetwork *> BrainPair;

    // collect all entities with brains
    std::vector<BrainPair> allEntities;
    entities.each<Brain>([this, &allEntities](entityx::Entity entity, Brain &b) {
        allEntities.emplace_back(entity, b.network);
    });

    // sort to find fittest
    // TODO what if numToTake > entity count?
    unsigned int numToTake = static_cast<unsigned int>(Config::TOP_PROPORTION_TO_TAKE * entities.size());
    std::partial_sort(allEntities.begin(), allEntities.begin() + numToTake, allEntities.end(),
                      [](BrainPair &a, BrainPair &b) {
                          return fitnessFunction(a.first) < fitnessFunction(b.first);
                      });

    // extract their brains
    std::vector<NeuralNetwork *> topBrains;
    topBrains.reserve(numToTake);
    for (BrainPair &e : allEntities) {
        topBrains.push_back(e.second);
    }

    // reset the world
    // don't access old entities from now on
    world.reset();
    entities.reset();

    // create a new generation from top, mutated brains
    std::vector<EntityDef> newGeneration;
    createEntitiesFromBrains(newGeneration, topBrains);
    spawnEntities(newGeneration);

    // delete old brains
    for (NeuralNetwork *&brain : topBrains)
        delete brain;
}

void Simulator::createEntitiesFromBrains(std::vector<EntityDef> &out, const std::vector<NeuralNetwork *> &brains) {

    for (int i = 0; i < Config::GENERATION_SIZE; ++i) {
        NeuralNetwork *newBrain = new NeuralNetwork;
        if (!brains.empty()) {
            NeuralNetwork *fitBrain = brains[i % brains.size()];
            fitBrain->copyAndMutate(newBrain);
        }

        float radius = Config::ENTITY_RADIUS;
        b2Vec2 randomPos(
                radius + (rand() % Config::WORLD_WIDTH) - radius - radius,
                radius + (rand() % Config::WORLD_HEIGHT) - radius - radius
        );

        EntityDef def(entities.create(), randomPos, &world, radius, newBrain);
        out.push_back(def);
    }
}

void Simulator::spawnEntities(const std::vector<EntityDef> &defs) {
    // on start of next tick
    queuedSpawns.insert(queuedSpawns.end(), defs.cbegin(), defs.cend());
}

b2World &Simulator::getPhysicsWorld() {
    return world.getPhysicsWorld();
}

unsigned int Simulator::getGenerationNumber() const {
    return generationNumber;
}

