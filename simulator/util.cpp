#include <cstdlib>
#include "util.h"
#include "config.h"

const double DEG_TO_RAD = M_PI / 180.0;
const double RAD_TO_DEG = 180.0 / M_PI;


b2Vec2 vecFromDegrees(float degrees, float length) {
    double radians = degrees * DEG_TO_RAD;
    return {static_cast<float32>(length * cos(radians)), static_cast<float32>(length * sin(radians))};
}


float degreesFromVec(const b2Vec2 &vec) {
    double radians = atan2(vec.y, vec.x);
    return static_cast<float>(radians * RAD_TO_DEG);
}

b2Vec2 randomPosition(float radius) {
    return {
            radius + (rand() % Config::WORLD_WIDTH) - radius - radius,
            radius + (rand() % Config::WORLD_HEIGHT) - radius - radius
    };
}

float interpolate(float value, std::pair<float, float> oldLimits, std::pair<float, float> newLimits) {
    float oldRange = oldLimits.second - oldLimits.first;
    float newRange = newLimits.second - newLimits.first;
    return (((value - oldLimits.first) * newRange) / oldRange) + newLimits.first;
}

VecPair calculateSensorVertices(float angle, float length, float offset) {
    b2Vec2 direction = vecFromDegrees(angle, 1);
    return {
            b2Vec2(direction.x * offset, direction.y * offset),
            b2Vec2(direction.x * (offset + length), direction.y * (offset + length))
    };
}
