#pragma once

namespace dudis
{
    class SizeF
    {
    public:
        float w;
        float h;

        SizeF(float w, float h) : w(w), h(h) {}
        SizeF() : w(0), h(0) {}

        SizeF operator+(const SizeF &other) const
        {
            return SizeF(w + other.w, h + other.h);
        }
    };

} // namespace dudis