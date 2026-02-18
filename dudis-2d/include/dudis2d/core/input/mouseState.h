#pragma once

namespace dudis
{
    enum class MouseButton
    {
        Left,
        Right,
        Middle,
        Side,
        Extra,
        Forward,
        Back,
        COUNT
    };

    struct ButtonState
    {
        bool down;
        bool pressed;
        bool released;
    };
}
