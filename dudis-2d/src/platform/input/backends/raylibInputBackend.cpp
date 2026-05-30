#include "dudis2d/platform/input/raylibInputBackend.h"

#include "dudis2d/platform/ddrlUtils/toRLKey.h"
#include "dudis2d/platform/ddrlUtils/toRLMouseButton.h"
#include "raylib.h"

using namespace dudis;

void RaylibInputBackend::update()
{
}

bool RaylibInputBackend::isKeyDown(KeyCode key) const
{
    int rk = ddrlUtils::toRaylibKey(key);

    if (rk == KEY_NULL)
    {
        return false;
    }

    return IsKeyDown(rk);
}

bool RaylibInputBackend::isMouseButtonDown(MouseButton button) const
{
    int rlButton = ddrlUtils::toRLMouseButton(button);

    if (rlButton < 0)
    {
        return false;
    }

    return IsMouseButtonDown(rlButton);
}

Vec2 RaylibInputBackend::getMousePosition() const
{
    auto position = GetMousePosition();
    return Vec2(position.x, position.y);
}

Vec2 RaylibInputBackend::getMousePositionScreen() const
{
    return getMousePosition();
}

Vec2 RaylibInputBackend::getMouseDelta() const
{
    auto delta = GetMouseDelta();
    return Vec2(delta.x, delta.y);
}

float RaylibInputBackend::getMouseWheel() const
{
    return GetMouseWheelMove();
}

Vec2 RaylibInputBackend::getMouseWheelDelta() const
{
    auto wheel = GetMouseWheelMoveV();
    return Vec2(wheel.x, wheel.y);
}
