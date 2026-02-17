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
            }
        }
    }
}