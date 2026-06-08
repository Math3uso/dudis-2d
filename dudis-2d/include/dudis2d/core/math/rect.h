#pragma once

#include <iostream>

namespace dudis
{
    struct DDRect
    {
        float x, y, w, h;

        constexpr DDRect(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
            : x(x), y(y), w(w), h(h) {}

        bool equals(const DDRect &other, float eps = 0.0001f) const
        {
            return std::abs(x - other.x) < eps &&
                   std::abs(y - other.y) < eps &&
                   std::abs(w - other.w) < eps &&
                   std::abs(h - other.h) < eps;
        }

        constexpr bool operator!=(const DDRect &other) const
        {
            return x != other.x || y != other.y || w != other.w || h != other.h;
        }

        constexpr bool operator==(const DDRect &other) const
        {
            return x == other.x && y == other.y && w == other.w && h == other.h;
        }

        float left() const { return x; }
        float right() const { return x + w; }
        float bottom() const { return y; }
        float top() const { return y + h; }

        bool intersects(const DDRect &other);
    };

    using Rect = DDRect;

    constexpr DDRect DDRECT_NONE{0, 0, 0, 0};
}