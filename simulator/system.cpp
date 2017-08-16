#include "system.h"
#include "component.h"
#include "neural.h"
#include "util.h"
#include "config.h"

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

}
