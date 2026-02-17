#include "dudis2d/core/input/input.h"
#include "dudis2d/core/input/keyboard.h"
#include "dudis2d/core/input/mouse.h"

using namespace dudis;

void Input::update()
{
    Keyboard::update();
    Mouse::update();
}