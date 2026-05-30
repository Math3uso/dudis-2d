#pragma once

namespace dudis
{
    template <typename T>
    class Size
    {
    public:
        T w;
        T h;

        Size(T w, T h) : w(w), h(h) {}

        bool operator==(const Size &other) const
        {
            return w == other.w && h == other.h;
        }

        Size operator+(const Size &other) const
        {
            return SizeI(w + other.w, h + other.h);
        }
    };

    // using SizeI = Size<int>;
    // using SizeF = Size<float>;
}