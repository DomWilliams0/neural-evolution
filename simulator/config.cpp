#include "config.h"

namespace Config {

    const int WORLD_WIDTH = 600;
    const int WORLD_HEIGHT = 600;
    const int TIME_GRANUALITY = 100;
    const float TIME_GRANUALITY_RECIP = static_cast<const float>(1.0 / TIME_GRANUALITY);

    const int TIME_PER_GENERATION = 10;
    const float TOP_PROPORTION_TO_TAKE = 0.2;
    const int GENERATION_SIZE = 10;
}
