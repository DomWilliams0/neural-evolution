#include "util.h"

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
