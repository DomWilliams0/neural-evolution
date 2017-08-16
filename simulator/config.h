#ifndef NEURAL_EVOLUTION_CONFIG_H
#define NEURAL_EVOLUTION_CONFIG_H

namespace Config {

    // world
    extern const int WORLD_WIDTH;
    extern const int WORLD_HEIGHT;
    extern const int TIME_GRANUALITY;
    extern const float TIME_GRANUALITY_RECIP;

    // generations
    extern const int TIME_PER_GENERATION;
    extern const float TOP_PROPORTION_TO_TAKE;
    extern const int GENERATION_SIZE;

    // mutations
    extern const float MUTATE_NORMAL_MEAN;
    extern const float MUTATE_NORMAL_SD;
    extern const float MUTATE_WEIGHT_CHANCE;

    // entity
    extern const float ENTITY_RADIUS;

}

#endif