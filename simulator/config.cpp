#include <vector.h>
#include "config.h"

namespace Config {

    const int WORLD_WIDTH = 1280;
    const int WORLD_HEIGHT = 800;
    const int TIME_GRANUALITY = 100;
    const float TIME_GRANUALITY_RECIP = static_cast<const float>(1.0 / TIME_GRANUALITY);
    const float TEMPERATURE_SCALE = 0.02; // smaller is more zoomed in

    const int TIME_PER_GENERATION = 10;
    const float TOP_PROPORTION_TO_TAKE = 1;
    const int GENERATION_SIZE = 50;

    const float FAST_FORWARD_TIME_SCALE = 0.2; // may fuck physics if too fast

    const float MUTATE_NORMAL_MEAN = 0.0; // middle value
    const float MUTATE_NORMAL_SD = 0.2; // variation
    const float MUTATE_WEIGHT_CHANCE = 0.04;

    const float ENTITY_RADIUS = 12;
    const float ENTITY_FORCE = 20;
    const float MAX_ENTITY_FORCE = 70;

    // 3 inputs (temp, time, food sensor)
    // 2 outputs (speed, direction)
    const std::vector<unsigned int> NET_LAYERS = {3, 3, 2};
    const std::pair<float, float> SENSOR_LENGTH_RANGE = {8, 48};

    const float INITIAL_FOOD_SIMULATION = 8; // seconds, so count = this/FOOD_SPAWN_RATE
    const float FOOD_NUTRITION = 3;
    const float FOOD_SPAWN_RATE = 0.1; // seconds
    const bool KEEP_SPAWNING_FOOD = true;

    const unsigned int FONT_SIZE_NORMAL_SPEED = 15;
    const unsigned int FONT_SIZE_FAST_FORWARD = 40;
}
