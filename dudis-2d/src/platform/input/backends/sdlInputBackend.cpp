#include "dudis2d/platform/input/sdlInputBackend.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>

using namespace dudis;

namespace
{
    SDL_Scancode toSDLScancode(KeyCode key)
    {
        using Key = KeyCode;

        switch (key)
        {
        case Key::Unknown:
            return SDL_SCANCODE_UNKNOWN;

        case Key::A:
            return SDL_SCANCODE_A;
        case Key::B:
            return SDL_SCANCODE_B;
        case Key::C:
            return SDL_SCANCODE_C;
        case Key::D:
            return SDL_SCANCODE_D;
        case Key::E:
            return SDL_SCANCODE_E;
        case Key::F:
            return SDL_SCANCODE_F;
        case Key::G:
            return SDL_SCANCODE_G;
        case Key::H:
            return SDL_SCANCODE_H;
        case Key::I:
            return SDL_SCANCODE_I;
        case Key::J:
            return SDL_SCANCODE_J;
        case Key::K:
            return SDL_SCANCODE_K;
        case Key::L:
            return SDL_SCANCODE_L;
        case Key::M:
            return SDL_SCANCODE_M;
        case Key::N:
            return SDL_SCANCODE_N;
        case Key::O:
            return SDL_SCANCODE_O;
        case Key::P:
            return SDL_SCANCODE_P;
        case Key::Q:
            return SDL_SCANCODE_Q;
        case Key::R:
            return SDL_SCANCODE_R;
        case Key::S:
            return SDL_SCANCODE_S;
        case Key::T:
            return SDL_SCANCODE_T;
        case Key::U:
            return SDL_SCANCODE_U;
        case Key::V:
            return SDL_SCANCODE_V;
        case Key::W:
            return SDL_SCANCODE_W;
        case Key::X:
            return SDL_SCANCODE_X;
        case Key::Y:
            return SDL_SCANCODE_Y;
        case Key::Z:
            return SDL_SCANCODE_Z;

        case Key::Num0:
            return SDL_SCANCODE_0;
        case Key::Num1:
            return SDL_SCANCODE_1;
        case Key::Num2:
            return SDL_SCANCODE_2;
        case Key::Num3:
            return SDL_SCANCODE_3;
        case Key::Num4:
            return SDL_SCANCODE_4;
        case Key::Num5:
            return SDL_SCANCODE_5;
        case Key::Num6:
            return SDL_SCANCODE_6;
        case Key::Num7:
            return SDL_SCANCODE_7;
        case Key::Num8:
            return SDL_SCANCODE_8;
        case Key::Num9:
            return SDL_SCANCODE_9;

        case Key::Escape:
            return SDL_SCANCODE_ESCAPE;
        case Key::Space:
            return SDL_SCANCODE_SPACE;
        case Key::Enter:
            return SDL_SCANCODE_RETURN;
        case Key::Tab:
            return SDL_SCANCODE_TAB;
        case Key::Backspace:
            return SDL_SCANCODE_BACKSPACE;
        case Key::Insert:
            return SDL_SCANCODE_INSERT;
        case Key::Delete:
            return SDL_SCANCODE_DELETE;
        case Key::Home:
            return SDL_SCANCODE_HOME;
        case Key::End:
            return SDL_SCANCODE_END;
        case Key::PageUp:
            return SDL_SCANCODE_PAGEUP;
        case Key::PageDown:
            return SDL_SCANCODE_PAGEDOWN;

        case Key::Left:
            return SDL_SCANCODE_LEFT;
        case Key::Right:
            return SDL_SCANCODE_RIGHT;
        case Key::Up:
            return SDL_SCANCODE_UP;
        case Key::Down:
            return SDL_SCANCODE_DOWN;

        case Key::CapsLock:
            return SDL_SCANCODE_CAPSLOCK;
        case Key::ScrollLock:
            return SDL_SCANCODE_SCROLLLOCK;
        case Key::NumLock:
            return SDL_SCANCODE_NUMLOCKCLEAR;
        case Key::PrintScreen:
            return SDL_SCANCODE_PRINTSCREEN;
        case Key::Pause:
            return SDL_SCANCODE_PAUSE;

        case Key::LeftShift:
            return SDL_SCANCODE_LSHIFT;
        case Key::RightShift:
            return SDL_SCANCODE_RSHIFT;
        case Key::LeftControl:
            return SDL_SCANCODE_LCTRL;
        case Key::RightControl:
            return SDL_SCANCODE_RCTRL;
        case Key::LeftAlt:
            return SDL_SCANCODE_LALT;
        case Key::RightAlt:
            return SDL_SCANCODE_RALT;
        case Key::LeftSuper:
            return SDL_SCANCODE_LGUI;
        case Key::RightSuper:
            return SDL_SCANCODE_RGUI;
        case Key::Menu:
            return SDL_SCANCODE_APPLICATION;

        case Key::F1:
            return SDL_SCANCODE_F1;
        case Key::F2:
            return SDL_SCANCODE_F2;
        case Key::F3:
            return SDL_SCANCODE_F3;
        case Key::F4:
            return SDL_SCANCODE_F4;
        case Key::F5:
            return SDL_SCANCODE_F5;
        case Key::F6:
            return SDL_SCANCODE_F6;
        case Key::F7:
            return SDL_SCANCODE_F7;
        case Key::F8:
            return SDL_SCANCODE_F8;
        case Key::F9:
            return SDL_SCANCODE_F9;
        case Key::F10:
            return SDL_SCANCODE_F10;
        case Key::F11:
            return SDL_SCANCODE_F11;
        case Key::F12:
            return SDL_SCANCODE_F12;
        case Key::F13:
            return SDL_SCANCODE_F13;
        case Key::F14:
            return SDL_SCANCODE_F14;
        case Key::F15:
            return SDL_SCANCODE_F15;
        case Key::F16:
            return SDL_SCANCODE_F16;
        case Key::F17:
            return SDL_SCANCODE_F17;
        case Key::F18:
            return SDL_SCANCODE_F18;
        case Key::F19:
            return SDL_SCANCODE_F19;
        case Key::F20:
            return SDL_SCANCODE_F20;
        case Key::F21:
            return SDL_SCANCODE_F21;
        case Key::F22:
            return SDL_SCANCODE_F22;
        case Key::F23:
            return SDL_SCANCODE_F23;
        case Key::F24:
            return SDL_SCANCODE_F24;

        case Key::Minus:
            return SDL_SCANCODE_MINUS;
        case Key::Equal:
            return SDL_SCANCODE_EQUALS;
        case Key::LeftBracket:
            return SDL_SCANCODE_LEFTBRACKET;
        case Key::RightBracket:
            return SDL_SCANCODE_RIGHTBRACKET;
        case Key::Backslash:
            return SDL_SCANCODE_BACKSLASH;
        case Key::Semicolon:
            return SDL_SCANCODE_SEMICOLON;
        case Key::Apostrophe:
            return SDL_SCANCODE_APOSTROPHE;
        case Key::Grave:
            return SDL_SCANCODE_GRAVE;
        case Key::Comma:
            return SDL_SCANCODE_COMMA;
        case Key::Period:
            return SDL_SCANCODE_PERIOD;
        case Key::Slash:
            return SDL_SCANCODE_SLASH;

        case Key::Numpad0:
            return SDL_SCANCODE_KP_0;
        case Key::Numpad1:
            return SDL_SCANCODE_KP_1;
        case Key::Numpad2:
            return SDL_SCANCODE_KP_2;
        case Key::Numpad3:
            return SDL_SCANCODE_KP_3;
        case Key::Numpad4:
            return SDL_SCANCODE_KP_4;
        case Key::Numpad5:
            return SDL_SCANCODE_KP_5;
        case Key::Numpad6:
            return SDL_SCANCODE_KP_6;
        case Key::Numpad7:
            return SDL_SCANCODE_KP_7;
        case Key::Numpad8:
            return SDL_SCANCODE_KP_8;
        case Key::Numpad9:
            return SDL_SCANCODE_KP_9;
        case Key::NumpadDecimal:
            return SDL_SCANCODE_KP_PERIOD;
        case Key::NumpadDivide:
            return SDL_SCANCODE_KP_DIVIDE;
        case Key::NumpadMultiply:
            return SDL_SCANCODE_KP_MULTIPLY;
        case Key::NumpadSubtract:
            return SDL_SCANCODE_KP_MINUS;
        case Key::NumpadAdd:
            return SDL_SCANCODE_KP_PLUS;
        case Key::NumpadEnter:
            return SDL_SCANCODE_KP_ENTER;
        case Key::NumpadEqual:
            return SDL_SCANCODE_KP_EQUALS;

        case Key::VolumeMute:
            return SDL_SCANCODE_MUTE;
        case Key::VolumeDown:
            return SDL_SCANCODE_VOLUMEDOWN;
        case Key::VolumeUp:
            return SDL_SCANCODE_VOLUMEUP;
        case Key::MediaPlayPause:
            return SDL_SCANCODE_MEDIA_PLAY_PAUSE;
        case Key::MediaStop:
            return SDL_SCANCODE_MEDIA_STOP;
        case Key::MediaNext:
            return SDL_SCANCODE_MEDIA_NEXT_TRACK;
        case Key::MediaPrev:
            return SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
        case Key::COUNT:
            return SDL_SCANCODE_UNKNOWN;
        }

        return SDL_SCANCODE_UNKNOWN;
    }

    Uint32 toSDLMouseButtonMask(MouseButton button)
    {
        switch (button)
        {
        case MouseButton::Left:
            return SDL_BUTTON_LMASK;
        case MouseButton::Right:
            return SDL_BUTTON_RMASK;
        case MouseButton::Middle:
            return SDL_BUTTON_MMASK;
        case MouseButton::Side:
        case MouseButton::Back:
            return SDL_BUTTON_X1MASK;
        case MouseButton::Extra:
        case MouseButton::Forward:
            return SDL_BUTTON_X2MASK;
        case MouseButton::COUNT:
            return 0;
        }

        return 0;
    }
}

void SDLInputBackend::update()
{
    SDL_PumpEvents();

    _keyboardState = SDL_GetKeyboardState(&_keyboardCount);

    float mouseX = 0.f;
    float mouseY = 0.f;
    _mouseButtonFlags = SDL_GetMouseState(&mouseX, &mouseY);
    _mousePosition = Vec2(mouseX, mouseY);

    float deltaX = 0.f;
    float deltaY = 0.f;
    SDL_GetRelativeMouseState(&deltaX, &deltaY);
    _mouseDelta = Vec2(deltaX, deltaY);

    _wheelDelta = _pendingWheelDelta;
    _pendingWheelDelta = Vec2(0.f, 0.f);
}

void SDLInputBackend::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_WHEEL)
    {
        _pendingWheelDelta.x += event.wheel.x;
        _pendingWheelDelta.y += event.wheel.y;
    }
}

bool SDLInputBackend::isKeyDown(KeyCode key) const
{
    SDL_Scancode scancode = toSDLScancode(key);

    if (_keyboardState == nullptr || scancode == SDL_SCANCODE_UNKNOWN || scancode >= _keyboardCount)
    {
        return false;
    }

    return _keyboardState[scancode];
}

bool SDLInputBackend::isMouseButtonDown(MouseButton button) const
{
    Uint32 mask = toSDLMouseButtonMask(button);
    return mask != 0 && (_mouseButtonFlags & mask) != 0;
}

Vec2 SDLInputBackend::getMousePosition() const
{
    return _mousePosition;
}

Vec2 SDLInputBackend::getMousePositionScreen() const
{
    return getMousePosition();
}

Vec2 SDLInputBackend::getMouseDelta() const
{
    return _mouseDelta;
}

float SDLInputBackend::getMouseWheel() const
{
    return _wheelDelta.y;
}

Vec2 SDLInputBackend::getMouseWheelDelta() const
{
    return _wheelDelta;
}
