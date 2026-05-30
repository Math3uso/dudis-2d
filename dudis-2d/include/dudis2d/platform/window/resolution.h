#pragma once

// #include "dudis2d/core/utils/types.h"
#include "dudis2d/core/math/vec2.h"
#include "dudis2d/core/utils/sizeF.h"

namespace dudis
{
    enum class ResolutionPolicy
    {
        Letterbox, // Com bordas
        Crop,
        Stretch,
        None // default
    };

    class ResolutionProps
    {
    public:
        Vec2 offset;
        float scale;
        ResolutionProps(Vec2 offset, float scale) : offset(offset), scale(scale) {}
    };

    class Resolution
    {
    public:
        SizeF size;
        ResolutionPolicy _policy;
        Resolution(SizeF size, ResolutionPolicy type) : size(size), _policy(type) {}
    };
}