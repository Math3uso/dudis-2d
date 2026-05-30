#include "dudis2d/platform/input/mouse.h"
#include "dudis2d/platform/input/input.h"

using namespace dudis;

ButtonState Mouse::_btState[(int)MouseButton::COUNT] = {0};

void Mouse::_beginFrame()
{
    for (auto &st : _btState)
    {
        st.pressed = false;
        st.released = false;
    }
}

void Mouse::update(InputBackend *backend)
{
    Mouse::_beginFrame();

    for (int i = 0; i < (int)MouseButton::COUNT; i++)
    {
        auto bt = (MouseButton)i;
        Mouse::_setMouseButton(bt, backend->isMouseButtonDown(bt));
    }
}

void Mouse::_setMouseButton(MouseButton bt, bool isDownNow)
{
    auto &btState = _btState[(int)bt];

    if (isDownNow && !btState.down)
        btState.pressed = true;

    if (!isDownNow && btState.down)
        btState.released = true;

    btState.down = isDownNow;
}

Vec2 Mouse::getPosition()
{
    return Input::getBackend()->getMousePosition();
}

Vec2 Mouse::getPositionScreen()
{
    return Input::getBackend()->getMousePositionScreen();
}

Vec2 Mouse::getDelta()
{
    return Input::getBackend()->getMouseDelta();
}

float Mouse::getWheel()
{
    return Input::getBackend()->getMouseWheel();
}

Vec2 Mouse::getWheelDelta()
{
    return Input::getBackend()->getMouseWheelDelta();
}
