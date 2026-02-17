#pragma once

#include "dudis2d/core/input/mouseState.h"
#include "dudis2d/core/math/vec2.h"

namespace dudis
{
    class Mouse
    {
    private:
        static ButtonState _btState[(int)MouseButton::COUNT];
        static void _setMouseButton(MouseButton, bool isDownNow);
        static void _beginFrame();
        static bool _getButtonsStateInRl(MouseButton bt);

    public:
        static void update();
        static bool isDown(MouseButton bt) { return _btState[(int)bt].down; };
        static bool isPressed(MouseButton bt) { return _btState[(int)bt].preesed; };
        static bool isReleased(MouseButton bt) { return _btState[(int)bt].released; };
        static Vec2 getPosition();
        static Vec2 getDelta();
        static float getWheel();
    };
}