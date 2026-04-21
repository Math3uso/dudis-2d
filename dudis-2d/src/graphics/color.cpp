#include "dudis2d/graphics/color.h"

void dudis::Color::opacity(float alpha)
{
    if (alpha < 0.0f)
    {
        alpha = 0.0f;
    }
    else if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }

    a = 255.f * alpha;
}