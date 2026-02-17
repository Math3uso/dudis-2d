#pragma once

#include "dudis2d/core/input/mouse.h"
#include "dudis2d/core/ddrlUtils/toRLMouseButton.h"
#include "raylib.h"

using namespace dudis;

ButtonState Mouse::_btState[(int)MouseButton::COUNT] = {0};

void Mouse::_beginFrame()
{
    for (auto &st : _btState)
    {
        st.preesed = false;
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
        btState.preesed = true;

    if (!isDownNow && btState.down)
        btState.released = true;

    btState.down = isDownNow;
}

bool Mouse::_getButtonsStateInRl(MouseButton bt)
{
    auto rlBt = ddrlUtils::toRLMouseButton(bt);

    return IsMouseButtonDown(rlBt);
}

Vec2 Mouse::getPosition()
{
    auto rlMousePos = GetMousePosition();

    return Vec2(rlMousePos.x, rlMousePos.y);
}