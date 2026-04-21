#include "dudis2d/platform/input/input.h"
#include "dudis2d/platform/input/keyboard.h"
#include "dudis2d/platform/input/mouse.h"

using namespace dudis;

void Input::update()
{
    Keyboard::update();
    Mouse::update();
}

int Input::getAxis(Axis axis)
{
    if (axis == Axis::Horizontal)
    {
        return dudis::Keyboard::isDown(KeyCode::D) - Keyboard::isDown(KeyCode::A);
    }
    return dudis::Keyboard::isDown(KeyCode::S) - Keyboard::isDown(KeyCode::W);
}
