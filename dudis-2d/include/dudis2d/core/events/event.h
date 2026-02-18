#pragma once

#include "dudis2d/core/events/eventType.h"

namespace dudis
{

    class Entity;

    class Event
    {
    public:
        Event() {};
        virtual ListenOnly type() {};
        // const EventType type;
        // const Entity *target;
        void consume();
        void accept();
    };
}