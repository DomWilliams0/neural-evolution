#include <plog/Log.h>
#include "system.h"
#include "neural.h"
#include "util.h"
#include "config.h"
#include "world.h"
#include "collision.h"


void NutritionSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    subscribe(this);
}

void SensorSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    subscribe(this);
}


void BrainSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<Brain, Physics>([this](entityx::Entity entity, Brain &brain, Physics &physics) {
        // gather inputs
        float time = world->getTime();
        float temp = world->getTemperature(physics.getPosition());
        std::vector<double> inputs = {time, temp};

        // feed forward
        std::vector<double> outputs;
        brain.network->tick(inputs, outputs);

        // parse outputs
        float speed = outputs[0] * Config::ENTITY_MAX_SPEED;
        float direction = static_cast<float>(outputs[1] * 360.f);

        // set from outputs
        physics.body->SetLinearVelocity(vecFromDegrees(direction, speed));
        physics.body->SetTransform(physics.body->GetPosition(), static_cast<float32>(direction * DEG_TO_RAD));
    });
}

void NutritionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

    if (Config::KEEP_SPAWNING_FOOD)
        foodTime += dt;

    while (foodTime >= Config::FOOD_SPAWN_RATE) {
        foodTime -= Config::FOOD_SPAWN_RATE;
        spawnRandomFood();
    }

}

void SensorSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

}

void NutritionSystem::onEvent(EatEvent &eat) {
    Consumer &consumer = eat.consumer;
    Nutrition &nutrition = eat.nutrition;

    if (nutrition.edible) {
        consumer.totalEaten += nutrition.nutrition;
        nutrition.edible = false;
    }

}
void SensorSystem::onEvent(FoodSenseEvent &sense) {
    sense.sensor.activated = sense.stimulated;
}


void NutritionSystem::spawnRandomFood() {
    float nutrition = Config::FOOD_NUTRITION;
    // TODO random range

    b2Fixture *fix = world->spawnFood(randomPosition(nutrition), nutrition * 2);
    ((UserData *) fix->GetUserData())->nutrition = nutrition;
}

void NutritionSystem::reset() {
    foodTime = Config::INITIAL_FOOD_SIMULATION;
}
