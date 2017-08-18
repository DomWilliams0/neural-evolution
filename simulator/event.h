#ifndef NEURAL_EVOLUTION_EVENT_H
#define NEURAL_EVOLUTION_EVENT_H

#include <entityx/Entity.h>
#include "component.h"

struct EatEvent {
    EatEvent(Consumer &consumer, Nutrition &nutrition) : consumer(consumer), nutrition(nutrition) {}

    Consumer consumer;
    Nutrition nutrition;

};


#endif
