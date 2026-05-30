#pragma once

#include "dudis2d/core/math/vec2.h"
#include "dudis2d/platform/input/key.h"
#include "dudis2d/platform/input/mouseState.h"

namespace dudis
{
    class InputBackend
    {
    public:
        virtual ~InputBackend() = default;

        virtual void update() = 0;

        virtual bool isKeyDown(KeyCode key) const = 0;
        virtual bool isMouseButtonDown(MouseButton button) const = 0;

        virtual Vec2 getMousePosition() const = 0;
        virtual Vec2 getMousePositionScreen() const = 0;
        virtual Vec2 getMouseDelta() const = 0;
        virtual float getMouseWheel() const = 0;
        virtual Vec2 getMouseWheelDelta() const = 0;
    };
}
