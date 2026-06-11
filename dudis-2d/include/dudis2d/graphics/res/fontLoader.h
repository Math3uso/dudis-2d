#pragma once

#include <vector>
#include <array>
#include "stb_truetype.h"

namespace dudis
{
    namespace FontLoader
    {
        struct FontData
        {
            std::vector<unsigned char> bitmaps;
            std::array<stbtt_bakedchar, 96> cdata;
        };
        FontData loadTTF(const char *path);
    };
}