#ifndef NEURAL_EVOLUTION_EVENT_H
#define NEURAL_EVOLUTION_EVENT_H

#include <entityx/Entity.h>
#include <event/Event.hpp>
#include <event/EventBus.hpp>
#include "component.h"

static Object NULL_OBJECT = Object();

template<typename E, typename ... Args>
void emit(Args &&... args) {
    E event(NULL_OBJECT, std::forward<Args>(args) ...);
    EventBus::FireEvent(event);
}

template<typename E>
void subscribe(EventHandler<E> *handler) {
    EventBus::AddHandler(*handler);
}

struct EatEvent : public Event {
    EatEvent(Object &sender, Consumer &consumer, Nutrition &nutrition)
            : Event(sender), consumer(consumer), nutrition(nutrition) {}

    Consumer &consumer;
    Nutrition &nutrition;
};


#endif
