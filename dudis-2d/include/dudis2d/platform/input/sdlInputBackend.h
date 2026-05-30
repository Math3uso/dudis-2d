#pragma once

#include "dudis2d/platform/input/inputBackend.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>

namespace dudis
{
    class SDLInputBackend : public InputBackend
    {
    public:
        SDLInputBackend() = default;

        void update() override;
        void handleEvent(const SDL_Event &event);

        bool isKeyDown(KeyCode key) const override;
        bool isMouseButtonDown(MouseButton button) const override;

        Vec2 getMousePosition() const override;
        Vec2 getMousePositionScreen() const override;
        Vec2 getMouseDelta() const override;
        float getMouseWheel() const override;
        Vec2 getMouseWheelDelta() const override;

    private:
        const bool *_keyboardState = nullptr;
        int _keyboardCount = 0;
        SDL_MouseButtonFlags _mouseButtonFlags = 0;
        Vec2 _mousePosition = Vec2(0.f, 0.f);
        Vec2 _mouseDelta = Vec2(0.f, 0.f);
        Vec2 _wheelDelta = Vec2(0.f, 0.f);
        Vec2 _pendingWheelDelta = Vec2(0.f, 0.f);
    };
}
