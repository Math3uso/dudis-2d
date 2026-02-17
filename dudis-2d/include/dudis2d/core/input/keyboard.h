#pragma once

#include "dudis2d/core/input/key.h"
#include "dudis2d/core/input/keyState.h"

namespace dudis
{
    class Keyboard
    {

    private:
        static KeyState _keys[DD_KEYS_COUNT];
        static void _beginFrames();
        static void _setKeyDown(Key key, bool isDownNow);
        static bool _getKeyDownIsRl(Key key);

    public:
        static void update();
        static bool isDown(Key key) { return _keys[(int)key].down; };
        static bool isPressed(Key key) { return _keys[(int)key].preesed; };
        static bool isUp(Key key) { return _keys[(int)key].released; };
    };
}