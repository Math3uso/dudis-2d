#pragma once

namespace dudis
{
    class SizeI
    {
    public:
        int w;
        int h;

        SizeI(int w, int h) : w(w), h(h) {}
        SizeI() : w(0), h(0) {}
    };
}