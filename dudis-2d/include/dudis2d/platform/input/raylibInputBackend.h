#pragma once

#include "dudis2d/platform/input/inputBackend.h"

namespace dudis
{
    class RaylibInputBackend : public InputBackend
    {
    public:
        void update() override;

        bool isKeyDown(KeyCode key) const override;
        bool isMouseButtonDown(MouseButton button) const override;

        Vec2 getMousePosition() const override;
        Vec2 getMousePositionScreen() const override;
        Vec2 getMouseDelta() const override;
        float getMouseWheel() const override;
        Vec2 getMouseWheelDelta() const override;
    };
}
