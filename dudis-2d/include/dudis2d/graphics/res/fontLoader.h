#pragma once

#include <vector>
#include <array>
#include <memory>
// #include <optional>
#include "stb_truetype.h"

namespace dudis
{
    namespace FontLoader
    {
        struct FontData
        {
            std::vector<unsigned char> bitmaps;
            std::array<stbtt_bakedchar, 96> cdata;
            int bitmapW;
            int bitmapH;
            float pixelH;
        };

        // constexpr FontData DD_INVALIDE_FONTE_DATA = {};
        constexpr std::vector<unsigned char> DD_INVALIDE_TTF_BUFFER;

        std::vector<unsigned char> createTTFBuffer(const char *path);
        FontData createFontWithTTFBuffer(std::vector<unsigned char> &buffer, float size = 32.f);

        FontData loadTTF(const char *path);
    };
}