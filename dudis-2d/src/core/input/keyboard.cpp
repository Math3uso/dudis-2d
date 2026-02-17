#include "dudis2d/core/input/keyboard.h"
#include "raylib.h"
#include "dudis2d/core/ddrlUtils/toRLKey.h"

using namespace dudis;

KeyState Keyboard::_keys[DD_KEYS_COUNT] = {};

void Keyboard::_beginFrames()
{
    for (auto &st : _keys)
    {
        st.preesed = false;
        st.released = false;
    }
}

void Keyboard::_setKeyDown(Key key, bool isDownNow)
{
    auto &st = _keys[(int)key];

    if (isDownNow && !st.down)
        st.preesed = true;

    if (!isDownNow && st.down)
        st.released = true;

    st.down = isDownNow;
};

void Keyboard::update()
{
    Keyboard::_beginFrames();
    for (int i = 0; i < DD_KEYS_COUNT; i++)
    {
        Key k = (Key)i;
        Keyboard::_setKeyDown(k, Keyboard::_getKeyDownIsRl(k));
    }
}

bool Keyboard::_getKeyDownIsRl(Key key)
{
    int rk = ddrlUtils::toRaylibKey(key);

    if (rk == KEY_NULL)
        return false;

    return IsKeyDown(rk);
}