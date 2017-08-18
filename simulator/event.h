#ifndef NEURAL_EVOLUTION_EVENT_H
#define NEURAL_EVOLUTION_EVENT_H

#include <entityx/Entity.h>
#include <event/Event.hpp>
#include <event/EventBus.hpp>
#include "component.h"

static Object NULL_OBJECT = Object();

template<typename E, typename ... Args>
void emit(Args &&... args) {
    E event(std::forward<Args>(args) ...);
    EventBus::FireEvent(event);
}

template<typename E>
void subscribe(EventHandler<E> *handler) {
    EventBus::AddHandler(*handler);
}

struct NeuralEvent : public Event {
    NeuralEvent() : Event(NULL_OBJECT) {}
};

struct EatEvent : public NeuralEvent {
    EatEvent(Consumer &consumer, Nutrition &nutrition) : consumer(consumer), nutrition(nutrition) {}

    Consumer &consumer;
    Nutrition &nutrition;
};

struct FoodSenseEvent : public NeuralEvent {
    FoodSenseEvent(FoodSensor &sensor, bool stimulated) : sensor(sensor), stimulated(stimulated) {}

    FoodSensor &sensor;
    bool stimulated;
};

#endif
