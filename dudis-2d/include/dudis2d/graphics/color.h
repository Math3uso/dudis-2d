#pragma once

#include <cstdint>
#include "dudis2d/core/math/vec4.h"

namespace dudis
{
    class Color
    {
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}

        constexpr Color() : r(0), g(0), b(0), a(255) {}

        void opacity(float a);

        static constexpr Color Red() { return Color(255, 0, 0, 255); }
        static constexpr Color Green() { return Color(0, 255, 0, 255); }
        static constexpr Color Blue() { return Color(0, 0, 255, 255); }

        static constexpr Color Default() { return Color(32, 32, 32, 255); }

        static constexpr Color White() { return Color(255, 255, 255, 255); }
        static constexpr Color Black() { return Color(0, 0, 0, 255); }

        static constexpr Color Hex(uint32_t color)
        {
            return Color(
                static_cast<uint8_t>((color >> 24) & 0xFF),
                static_cast<uint8_t>((color >> 16) & 0xFF),
                static_cast<uint8_t>((color >> 8) & 0xFF),
                static_cast<uint8_t>(color & 0xFF));
        }

        constexpr bool operator==(const Color &other) const
        {
            return r == other.r && g == other.g && b == other.b;
        }

        constexpr uint32_t operator!=(const Color &other) const
        {
            return !(*this == other);
        }

        constexpr uint32_t packed() const
        {
            return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)g << 8) | ((uint32_t)r << 0);
        }

        Vec4 normalized() const
        {
            return Vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        }
    };
}
