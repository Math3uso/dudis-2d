#pragma once

#include "dudis2d/graphics/ddAssets/ddTextureTypeUtils.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        res::TextureFormat mapRaylibFormat(PixelFormat fmt);

        PixelFormat mapToRaylibFormat(res::TextureFormat fmt);
    } // namespace ddrlUtils
} // namespace dudis