#pragma once

#include <cstdint>

namespace dudis
{
    namespace ddgl
    {

        struct ddgl_color
        {
            float r, g, b, a;
        };

        // empacotar 4 valores em 1 uint32_t
        inline uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | ((uint32_t)a << 0);
        }

        // convertendo cores pra GPU
        inline uint8_t colorR(uint32_t c) { return (c >> 24) & 0xFF; }
        inline uint8_t colorG(uint32_t c) { return (c >> 16) & 0xFF; }
        inline uint8_t colorB(uint32_t c) { return (c >> 8) & 0xFF; }
        inline uint8_t colorA(uint32_t c) { return (c >> 0) & 0xFF; }

        inline ddgl_color normalize(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            return {r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
        };

    }
}
