#ifndef NEURAL_EVOLUTION_MATH_H
#define NEURAL_EVOLUTION_MATH_H

#include <Box2D/Common/b2Math.h>
#include <utility>

extern const double DEG_TO_RAD;
extern const double RAD_TO_DEG;

using VecPair = std::pair<b2Vec2, b2Vec2>;

b2Vec2 vecFromDegrees(float degrees, float length = 1);

float degreesFromVec(const b2Vec2 &vec);

b2Vec2 randomPosition(float radius);

float interpolate(float value, std::pair<float, float> oldLimits, std::pair<float, float> newLimits);

VecPair calculateSensorVertices(float angle, float length, float offset);


#endif