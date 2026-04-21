#pragma once

#include "dudis2d/graphics/ddAssets/ddTextureTypeUtils.h"
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"

namespace dudis
{
    // Usar o prefixo RL para nas funções desse namespace
    namespace ddrlUtils
    {
        res::TextureFormat mapRaylibFormat(unsigned int fmt);

        unsigned int mapToRaylibFormat(res::TextureFormat fmt);

        unsigned int mapToRLFilter(res::DDTextureFilter filter);
    } // namespace ddrlUtils
} // namespace dudis