#ifndef NEURAL_EVOLUTION_CONFIG_H
#define NEURAL_EVOLUTION_CONFIG_H

#include <vector>

namespace Config {

    // world
    extern const int WORLD_WIDTH;
    extern const int WORLD_HEIGHT;
    extern const int TIME_GRANUALITY;
    extern const float TIME_GRANUALITY_RECIP;
    extern const float TEMPERATURE_SCALE;

    // generations
    extern const int TIME_PER_GENERATION;
    extern const float TOP_PROPORTION_TO_TAKE;
    extern const int GENERATION_SIZE;

    // fast forward
    extern const float FAST_FORWARD_TIME_SCALE;

    // mutations
    extern const float MUTATE_NORMAL_MEAN;
    extern const float MUTATE_NORMAL_SD;
    extern const float MUTATE_WEIGHT_CHANCE;

    // entity
    extern const float ENTITY_RADIUS;
    extern const float ENTITY_MAX_SPEED;
    extern const std::vector<unsigned int> NET_LAYERS;
    extern const std::pair<float, float> SENSOR_LENGTH_RANGE;

    // food
    // TODO nutrition range
    extern const float INITIAL_FOOD_SIMULATION;
    extern const float FOOD_NUTRITION;
    extern const float FOOD_SPAWN_RATE;
    extern const bool KEEP_SPAWNING_FOOD;

    // renderer
    extern const unsigned int FONT_SIZE_NORMAL_SPEED;
    extern const unsigned int FONT_SIZE_FAST_FORWARD;
}

#endif