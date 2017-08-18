#include <vector>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

#include "simulator.h"
#include "system.h"
#include "neural.h"
#include "collision.h"

void initLogger() {
    static plog::ColorConsoleAppender<plog::TxtFormatter> appender;
    plog::init(plog::debug, &appender);
}


Simulator::Simulator() : generationTime(Config::TIME_PER_GENERATION),
                         generationNumber(0) {
    initLogger();

    // seed random for OpenNN
    srand(time(NULL));

    // register systems
    systems.add<BrainSystem>(&this->world);
    systems.add<NutritionSystem>(&this->world);
    systems.add<SensorSystem>();

    systems.configure();

    // create first generation from nothing
    startNewGeneration();
}

static void addSensor(entityx::Entity &entity, float angle, float length) {
    float realAngle = angle * 360.f;
    float realLength = interpolate(length, {0.f, 1.f}, Config::SENSOR_LENGTH_RANGE);

    entity.assign<FoodSensor>(realAngle, realLength);

    entityx::ComponentHandle<Physics> phys = entity.component<Physics>();
    std::pair<b2Vec2, b2Vec2> vertices(calculateSensorVertices(realAngle, realLength, phys->radius));

    b2EdgeShape edge;
    edge.Set(vertices.first, vertices.second);

    UserData *userData = new UserData(EntityType::FOOD_SENSOR);
    userData->entity = entity;

    b2FixtureDef def;
    def.userData = userData;
    def.shape = &edge;
    def.isSensor = true;

    phys->body->CreateFixture(&def);
}

void Simulator::tick(float dt) {
    generationTime -= dt;

    if (generationTime < 0)
        startNewGeneration();

    // populate new entities
    for (EntityDef &def : queuedSpawns) {
        def.id.assign<Brain>(def.brain ? def.brain : new NeuralNetwork);
        def.id.assign<Consumer>();

        // physics
        b2Body *body = nullptr;
        b2Fixture *fixture = nullptr;
        def.world->spawnEntity(def.pos, def.radius, &body, &fixture);
        def.id.assign<Physics>(body, fixture, def.radius);
        ((UserData *) fixture->GetUserData())->entity = def.id;

        addSensor(def.id, 0.25, 0.5);
    }
    queuedSpawns.clear();

    world.tick(dt);
    systems.update_all(dt);
}

float fitnessFunction(entityx::Entity &entity) {
    return entity.component<Consumer>()->totalEaten;
}

void Simulator::startNewGeneration() {
    // reset clock
    generationTime = Config::TIME_PER_GENERATION;

    typedef std::pair<entityx::Entity, NeuralNetwork *> BrainPair;

    // collect all entities with brains
    std::vector<BrainPair> allEntities;
    entities.each<Brain>([this, &allEntities](entityx::Entity entity, Brain &b) {
        allEntities.emplace_back(entity, b.network);
    });

    // sort to find fittest
    // TODO what if numToTake > entity count?
    unsigned int numToTake = static_cast<unsigned int>(Config::TOP_PROPORTION_TO_TAKE * entities.size());
    std::sort(allEntities.begin(), allEntities.end(),
              [](BrainPair &a, BrainPair &b) {
                  return fitnessFunction(a.first) > fitnessFunction(b.first);
                      });

    if (!allEntities.empty()) {
        LOGI << "Most food collected in generation " << generationNumber << ": "
             << fitnessFunction(allEntities[0].first);
    }

    // extract their brains
    std::vector<NeuralNetwork *> topBrains;
    topBrains.reserve(numToTake);
    for (size_t i = 0; i < numToTake && i < allEntities.size(); ++i) {
        topBrains.push_back(allEntities[i].second);
    }

    // reset the world
    // don't access old entities from now on
    world.reset();
    entities.reset();
    systems.system<NutritionSystem>()->reset();

    // create a new generation from top, mutated brains
    std::vector<EntityDef> newGeneration;
    createEntitiesFromBrains(newGeneration, topBrains);
    spawnEntities(newGeneration);

    // delete old brains
    for (NeuralNetwork *&brain : topBrains)
        delete brain;

    generationNumber += 1;
    LOG_DEBUG << "New generation " << generationNumber;
}

void Simulator::createEntitiesFromBrains(std::vector<EntityDef> &out, const std::vector<NeuralNetwork *> &brains) {

    for (int i = 0; i < Config::GENERATION_SIZE; ++i) {
        NeuralNetwork *newBrain = new NeuralNetwork;
        if (!brains.empty()) {
            NeuralNetwork *fitBrain = brains[i % brains.size()];
            fitBrain->copyAndMutate(newBrain);
        }

        float radius = Config::ENTITY_RADIUS;
        EntityDef def(entities.create(), randomPosition(radius), &world, radius, newBrain);
        out.push_back(def);
    }
}

void Simulator::spawnEntities(const std::vector<EntityDef> &defs) {
    // on start of next tick
    queuedSpawns.insert(queuedSpawns.end(), defs.cbegin(), defs.cend());
}

World &Simulator::getWorld() {
    return world;
}

unsigned int Simulator::getGenerationNumber() const {
    return generationNumber;
}

