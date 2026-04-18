#pragma once

#include <functional>
#include <memory>
#include "dudis2d/core/math/vec2.h"

namespace dudis
{

    class Entity;

    class Motion
    {
    protected:
        float _duration = 0; // quando tempo deve durar em segundos
        float _elapsed = 0;  // quanto tempo já passou
        bool _start = false;
        bool _isDone = false;
        Vec2 _from;
        Vec2 _to;

        std::function<float(float t)> _easing;
        std::function<void()> _onComplete;
        Entity *_target;

    public:
        Motion(Vec2 to, float duration) : _to(to), _duration(duration) {};
        virtual void update();
        virtual void step() {};
        virtual void startWithTarget(Entity *target);

        bool isDone() { return _isDone; }

        void onComplete(std::function<void()> callback) { _onComplete = std::move(callback); }

        template <auto Fn>
        static std::shared_ptr<Motion> create(Vec2 to, float duration)
        {
            auto motion = std::make_shared<Motion>(to, duration);
            motion->_easing = Fn;
            return motion;
        };
    };
}