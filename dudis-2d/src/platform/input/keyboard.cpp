#include "dudis2d/platform/input/keyboard.h"

using namespace dudis;

KeyState Keyboard::_keys[Keyboard::_keysCount] = {};

void Keyboard::_beginFrames()
{
    for (auto &st : _keys)
    {
        st.pressed = false;
        st.released = false;
    }
}

void Keyboard::_setKeyDown(KeyCode key, bool isDownNow)
{
    auto &st = _keys[(int)key];

    if (isDownNow && !st.down)
        st.pressed = true;

    if (!isDownNow && st.down)
        st.released = true;

    st.down = isDownNow;
};

void Keyboard::update(InputBackend *backend)
{
    Keyboard::_beginFrames();
    for (int i = 0; i < _keysCount; i++)
    {
        KeyCode k = (KeyCode)i;
        Keyboard::_setKeyDown(k, backend->isKeyDown(k));
    }
}
