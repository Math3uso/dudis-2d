#pragma once

namespace dudis
{
    enum class MouseButton
    {
        Left,
        Right,
        Middle,
        COUNT
    };

    struct ButtonState
    {
        bool down;
        bool preesed;
        bool released;
    };
}