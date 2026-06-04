#pragma once

#include <cstdint>
#include <vector>
#include "dudis2d/core/math/vec2.h"
#include "dudis2d/core/utils/sizeF.h"
#include "dudis2d/core/math/rect.h"

namespace dudis
{

    namespace ddgl
    {

        constexpr uint32_t DD_MAX_DRAWCALL = 4096; // max draw call by frame
        constexpr uint32_t DD_MAX_TEXTURES = 16;   // slots de textura por batch (limite GLES)
        constexpr uint32_t DD_MAX_VERTEX = 65536;  // 64k vértices por batch
        constexpr uint32_t DD_MAX_QUADS = DD_MAX_VERTEX / 4;
        constexpr uint32_t DD_MAX_INDEX = DD_MAX_QUADS * 6;

        constexpr uint32_t DD_INVALID_TEXTURE_ID = -1;
        constexpr uint32_t DD_WHITE_TEXTURE_ID = 0;

        enum class ShaderType
        {
            VERT,
            FRAG,
        };

        enum class PrimitiveType
        {
            Triangles,
            Lines,
            LineStrip,
            Points,
        };

        enum class PoligonMode
        {
            Fill,
            Line,
            Point,
        };

        enum class BlendMode
        {
            Alpha,
            Additive,
            Multiply,
            None,
        };

        // enum class TextureFilter
        // {
        //     Nearest,
        //     Linear,
        // };

        struct DDVertex_V3F_C4B_U2F
        {
            float x, y;
            float u, v;
            uint32_t color;
        };

        using DDVertex = DDVertex_V3F_C4B_U2F;

        struct DDVertexV3FC4B
        {
            float x, y;
            uint32_t color;
        };

        struct ShaderHandle
        {
            uint32_t shader;
            ShaderType type;
            const char *src;
        };

        constexpr ShaderHandle SHADER_INVALID = ShaderHandle{0};

        struct DDTexture2D
        {
            uint32_t id;
            int width;
            int height;
            int mipLevels;
        };

        constexpr DDTexture2D DD_WHITE_TEXTURE = {.id = DD_WHITE_TEXTURE_ID, .width = 1, .height = 1, .mipLevels = 1};
        constexpr DDRect DD_NONE_TEXTURE_RECT = DDRect{0, 0, 1, 1};

        using TextureHandle = DDTexture2D;

        struct FrameBuffer
        {
            uint32_t id;
            DDTexture2D texture;
            int width;
            int height;
        };

        enum class SamplerFilter
        {
            Nearest, // sem interpolação, pixel perfeito. Bom para pixel art e gráficos nítidos.
            Linear,  // interpola os pixels vizinhos, resultando em uma aparência mais suave. Bom para gráficos realistas ou quando a textura é ampliada.
        };
        enum class SamplerWrap
        {
            Repeat,         // a textura se repete quando as coordenadas UV ultrapassam o intervalo [0, 1]. Bom para superfícies grandes ou padrões repetitivos.
            ClampToEdge,    // a textura é limitada aos bordos, evitando repetição.
            MirroredRepeat, // a textura é repetida de forma espelhada. Bom para criar padrões simétricos.'
        };
        struct DDTextureSampler
        {
            SamplerFilter minFilter; // filtro de minificação (quando a textura é reduzida)
            SamplerFilter magFilter; // filtro de magnificação (quando a textura é ampliada)
            SamplerWrap wrapS;       // comportamento de repetição no eixo S (horizontal)
            SamplerWrap wrapT;       // comportamento de repetição no eixo T (vertical)

            DDTextureSampler(SamplerFilter minFilter = SamplerFilter::Nearest,
                             SamplerFilter magFilter = SamplerFilter::Nearest,
                             SamplerWrap wrapS = SamplerWrap::Repeat,
                             SamplerWrap wrapT = SamplerWrap::Repeat)
                : minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}

            static DDTextureSampler uniform(
                SamplerFilter filter,
                SamplerWrap wrap)
            {
                return DDTextureSampler(
                    filter,
                    filter,
                    wrap,
                    wrap);
            }

            void operator=(const DDTextureSampler &other)
            {
                minFilter = other.minFilter;
                magFilter = other.magFilter;
                wrapS = other.wrapS;
                wrapT = other.wrapT;
            }

            bool operator==(const DDTextureSampler &other) const
            {
                return minFilter == other.minFilter &&
                       magFilter == other.magFilter &&
                       wrapS == other.wrapS &&
                       wrapT == other.wrapT;
            }

            bool operator!=(const DDTextureSampler &other) const
            {
                return !(*this == other);
            }
        };

        using DDSampler = DDTextureSampler;

        using DDRenderTarget = FrameBuffer;

        constexpr FrameBuffer DD_INVALID_FRAMEBUFFER = FrameBuffer{0};

        struct VertexQuadData
        {
            VertexQuadData() { vertices.reserve(4); };

            std::vector<DDVertexV3FC4B> vertices;
            std::vector<uint32_t> indices;
        };

        struct VertexQuadDataTextured
        {
            VertexQuadDataTextured() { vertices.reserve(4); };
            std::vector<DDVertex_V3F_C4B_U2F> vertices;
            std::vector<uint32_t> indices;
            uint32_t textureId;

            SizeF _size;
            Vec2 _pos;
        };

        VertexQuadDataTextured createQuadData(const SizeF &size, const Vec2 &pos, const Rect &src, uint32_t color, DDTexture2D img);

        struct DDGLDrawCommand
        {
            int startVertex;
            int vertexCount;
            int startIndex;
            int indexCount;
            uint32_t textureId;
        };

        struct DDTransform2D
        {
            Vec2 position;
            Vec2 scale = Vec2{1.f, 1.f};
            Vec2 origin = Vec2{0.f, 0.f};
            float rotation = 0.f; // radianos
            float skewX = 0.0f;   // radianos
            float skewY = 0.0f;   // radianos
        };

        constexpr bool DD_REPLACE_POS = true;
        constexpr bool DD_KEEP_POS = false;

        void transformQuadV3FC4B(const DDTransform2D &transform, std::vector<DDVertexV3FC4B> &quad);

        void transformDDVertex(const DDTransform2D &transform, VertexQuadDataTextured &vertexData, bool replacePos = false);
    }
}
