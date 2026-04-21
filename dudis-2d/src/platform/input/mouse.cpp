#pragma once

#include "dudis2d/platform/input/mouse.h"
#include "dudis2d/platform/ddrlUtils/toRLMouseButton.h"
#include "raylib.h"

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

void Mouse::update()
{
    Mouse::_beginFrame();

    for (int i = 0; i < (int)MouseButton::COUNT; i++)
    {
        auto bt = (MouseButton)i;
        Mouse::_setMouseButton(bt, Mouse::_getButtonsStateInRl(bt));
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

bool Mouse::_getButtonsStateInRl(MouseButton bt)
{
    auto rlBt = ddrlUtils::toRLMouseButton(bt);

    if (rlBt < 0)
        return false;

    return IsMouseButtonDown(rlBt);
}

Vec2 Mouse::getPosition()
{
    auto rlMousePos = GetMousePosition();

    return Vec2(rlMousePos.x, rlMousePos.y);
}

Vec2 Mouse::getPositionScreen()
{
    return Mouse::getPosition();
}

Vec2 Mouse::getDelta()
{
    auto rlDelta = GetMouseDelta();

    return Vec2(rlDelta.x, rlDelta.y);
}

float Mouse::getWheel()
{
    return GetMouseWheelMove();
}

Vec2 Mouse::getWheelDelta()
{
    auto rlWheel = GetMouseWheelMoveV();

    return Vec2(rlWheel.x, rlWheel.y);
}
