#ifndef NEURAL_EVOLUTION_MATH_H
#define NEURAL_EVOLUTION_MATH_H

#include <Box2D/Common/b2Math.h>

extern const double DEG_TO_RAD;
extern const double RAD_TO_DEG;

b2Vec2 vecFromDegrees(float degrees, float length = 1);

float degreesFromVec(const b2Vec2 &vec);

b2Vec2 randomPosition(float radius);

#endif