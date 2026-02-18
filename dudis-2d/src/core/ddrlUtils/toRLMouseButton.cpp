#include "dudis2d/core/ddrlUtils/toRLMouseButton.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        int toRLMouseButton(MouseButton bt)
        {
            switch (bt)
            {
            case MouseButton::Left:
                return MOUSE_BUTTON_LEFT;

            case MouseButton::Right:
                return MOUSE_BUTTON_RIGHT;

            case MouseButton::Middle:
                return MOUSE_BUTTON_MIDDLE;

            case MouseButton::Side:
                return MOUSE_BUTTON_SIDE;

            case MouseButton::Extra:
                return MOUSE_BUTTON_EXTRA;

            case MouseButton::Forward:
                return MOUSE_BUTTON_FORWARD;

            case MouseButton::Back:
                return MOUSE_BUTTON_BACK;
            }

            return -1;
        }
    }
}
