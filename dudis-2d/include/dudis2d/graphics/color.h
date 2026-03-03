#pragma once

#include <cstdint>

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
    };
}