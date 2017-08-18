#include <vector.h>
#include "config.h"

namespace Config {

    const int WORLD_WIDTH = 600;
    const int WORLD_HEIGHT = 600;
    const int TIME_GRANUALITY = 100;
    const float TIME_GRANUALITY_RECIP = static_cast<const float>(1.0 / TIME_GRANUALITY);
    const float TEMPERATURE_SCALE = 0.02; // smaller is more zoomed in

    const int TIME_PER_GENERATION = 5;
    const float TOP_PROPORTION_TO_TAKE = 0.25;
    const int GENERATION_SIZE = 30;

    const float FAST_FORWARD_TIME_SCALE = 10; // may fuck physics if too fast
    const unsigned int FAST_FORWARD_ITERATIONS = 10; // TODO not good to hardcode, just go as fast as possible

    const float MUTATE_NORMAL_MEAN = 0.0; // middle value
    const float MUTATE_NORMAL_SD = 0.2; // variation
    const float MUTATE_WEIGHT_CHANCE = 0.04;

    const float ENTITY_RADIUS = 10;
    const float ENTITY_MAX_SPEED = 50;

    // 2 inputs (temp, time)
    // 2 outputs (speed, direction)
    const std::vector<unsigned int> NET_LAYERS = {2, 3, 2};

    const unsigned int FONT_SIZE_NORMAL_SPEED = 15;
    const unsigned int FONT_SIZE_FAST_FORWARD = 40;
}
