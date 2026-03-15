#pragma once

#include "dudis2d/graphics/ddAssets/ddTextureTypeUtils.h"
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"
#include "raylib.h"

namespace dudis
{
    // Usar o prefixo RL para nas funções desse namespace
    namespace ddrlUtils
    {
        res::TextureFormat mapRaylibFormat(PixelFormat fmt);

        PixelFormat mapToRaylibFormat(res::TextureFormat fmt);

        unsigned int mapToRLFilter(res::DDTextureFilter filter);
    } // namespace ddrlUtils
} // namespace dudis