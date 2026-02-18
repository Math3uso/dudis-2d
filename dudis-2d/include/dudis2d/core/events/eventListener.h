#pragma once

#include <functional>
#include <memory>
#include "dudis2d/core/events/eventType.h"
#include "dudis2d/core/events/event.h"

namespace dudis
{
    class EventListener
    {
    private:
        std::function<void(const Event &event)> _callback;

    public:
        static std::shared_ptr<EventListener> create() {};
        virtual void addListener(ListenOnly type) {};
        virtual void handleCallback() = 0;
        void removeListener() {};
    };
}