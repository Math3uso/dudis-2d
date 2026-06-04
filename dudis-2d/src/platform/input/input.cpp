#include "dudis2d/platform/input/input.h"
#include "dudis2d/platform/input/keyboard.h"
#include "dudis2d/platform/input/mouse.h"
#include "dudis2d/platform/input/sdlInputBackend.h"

using namespace dudis;

std::unique_ptr<InputBackend> Input::_backend = nullptr;

void Input::update()
{
    auto *backend = Input::getBackend();

    backend->update();
    Keyboard::update(backend);
    Mouse::update(backend);
}

int Input::getAxis(Axis axis)
{
    if (axis == Axis::Horizontal)
    {
        return dudis::Keyboard::isDown(KeyCode::D) - Keyboard::isDown(KeyCode::A);
    }
    return dudis::Keyboard::isDown(KeyCode::S) - Keyboard::isDown(KeyCode::W);
}

void Input::setBackend(InputBackendType type)
{
    switch (type)
    {
    case InputBackendType::SDL:
        _backend = std::make_unique<SDLInputBackend>();
        break;
    case InputBackendType::RL:
        _backend = std::make_unique<SDLInputBackend>();
        break;
    default:
        _backend = nullptr;
        break;
    }
}

InputBackend *Input::getBackend()
{
    if (!_backend)
    {
        Input::setBackend(InputBackendType::SDL);
    }

    return _backend.get();
}
