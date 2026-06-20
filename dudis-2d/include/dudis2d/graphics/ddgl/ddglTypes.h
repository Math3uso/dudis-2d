#pragma once

#include <cstdint>
#include <vector>
#include "dudis2d/core/math/vec2.h"
#include "dudis2d/core/utils/sizeF.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/graphics/res/fontLoader.h"

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

        constexpr uint32_t DD_WHITE_TEXTURE_PIXEL = 0xFFFFFFFF;
        constexpr uint32_t DD_PROGRAM_DEFAULT = 0;

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

        enum class PilelineState
        {
            Draw,
            Scissor,
            EndScissor,
            // Stencil,
            Blend,
        };

        enum class RenderMode
        {
            Texture,
            Font
        };

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

            /// Cria um sampler usando o mesmo filtro para minificação e magnificação
            /// e o mesmo modo de repetição para os eixos S e T.
            ///
            /// @param filter Filtro aplicado tanto quando a textura diminui quanto quando aumenta.
            /// @param wrap Modo de repetição aplicado nos dois eixos de coordenada da textura.
            /// @return Um DDTextureSampler com todos os campos preenchidos de forma uniforme.
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

        enum class DDColorFormat
        {
            RGBA,
            RGB,
            R8,
            RED,
        };

        struct DDTexInternalFormat
        {
            DDColorFormat storageFormat; // como a GPU guarda
            DDColorFormat sourceLayout;  // como enviamos antes de guardar

            DDTexInternalFormat(DDColorFormat format, DDColorFormat src) { storageFormat = format, sourceLayout = src; }

            DDTexInternalFormat() = default;

            /// Cria uma configuração comum para texturas RGBA.
            ///
            /// Usa RGBA tanto como formato interno da GPU quanto como layout dos dados
            /// enviados pela CPU.
            ///
            /// @return Configuração de formato para texturas com canais vermelho, verde,
            /// azul e alfa.
            static DDTexInternalFormat RGBA() { return DDTexInternalFormat(DDColorFormat::RGBA, DDColorFormat::RGBA); }

            /// Cria uma configuração para texturas de um canal armazenadas como R8.
            ///
            /// O armazenamento interno usa R8 e os dados de entrada são interpretados
            /// pelo canal RED. Esse formato é útil para mapas de máscara, fontes e
            /// outras texturas que precisam de apenas um canal.
            ///
            /// @return Configuração de formato para textura de canal único.
            static DDTexInternalFormat R8_RED() { return DDTexInternalFormat(DDColorFormat::R8, DDColorFormat::RED); }
        };

        using TexInternalFormat = DDTexInternalFormat;

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

            uint32_t programShader = 0; // shader específico para este quad, se 0 usa o shader padrão do batch

            SizeF _size;
            Vec2 _pos;
        };

        /// Cria os dados de vértices e índices para desenhar um quad texturizado.
        ///
        /// A função monta quatro vértices em ordem horária a partir do canto superior
        /// esquerdo de `pos`, calcula as coordenadas UV usando `src` dentro da textura
        /// `img` e gera os seis índices necessários para formar dois triângulos.
        ///
        /// @param size Largura e altura finais do quad em coordenadas de tela/mundo.
        /// @param pos Posição do canto superior esquerdo do quad.
        /// @param src Retângulo da região da textura que será usada. As coordenadas
        /// são dadas em pixels da textura.
        /// @param color Cor aplicada a todos os vértices. Normalmente é usada como
        /// multiplicador/tint no shader.
        /// @param img Textura de origem. O campo `id` é guardado no quad e `width`/
        /// `height` são usados para normalizar as UVs.
        /// @return Um VertexQuadDataTextured pronto para ser enviado ao batch de render.
        VertexQuadDataTextured createQuadData(const SizeF &size, const Vec2 &pos, const Rect &src, uint32_t color, DDTexture2D img);

        /// Cria os dados de vértices e índices para desenhar uma sequência de texto.
        ///
        /// Para cada caractere de `text`, a função consulta as métricas baked da fonte,
        /// cria um quad com as UVs corretas no atlas e avança a posição de escrita.
        /// O texto gerado usa a textura informada em `tex`.
        ///
        /// @param font Dados da fonte carregada, incluindo as informações baked dos glifos.
        /// @param text Texto terminado em `\0` que será convertido em quads.
        /// @param size Tamanho solicitado para o texto. Atualmente a implementação não
        /// usa esse valor para escalar os vértices.
        /// @param pos Posição inicial onde o texto será desenhado. A função recebe por
        /// valor, então o cursor interno pode avançar sem alterar o Vec2 original.
        /// @param tex Textura/atlas que contém os glifos da fonte.
        /// @param color Cor aplicada a todos os vértices dos glifos.
        /// @return Um VertexQuadDataTextured com todos os quads e índices do texto.
        VertexQuadDataTextured createTexteQuad(FontLoader::FontData &font, const char *text, int size, Vec2 pos, DDTexture2D tex, uint32_t color);

        struct DDGLDrawCommand
        {
            PilelineState state;
            int startVertex;
            int vertexCount;
            int startIndex;
            int indexCount;
            uint32_t textureId;
            uint32_t programShader; // shader específico para este comando, se 0 usa o shader padrão do batch
            DDRect scissorRect;     // retângulo de recorte, se aplicável
            RenderMode mode;
        };

        class DDGLDrawBatch
        {
        private:
            std::vector<DDGLDrawCommand> drawCommands;
            int lastSize = 0;

        public:
            /// Agrupa comandos de desenho consecutivos compatíveis.
            ///
            /// Dois comandos são considerados compatíveis quando usam a mesma textura,
            /// o mesmo shader, o mesmo estado de pipeline e o mesmo modo de render.
            /// Nesses casos, a função soma as contagens de vértices e índices no comando
            /// anterior, reduzindo a quantidade de draw calls que o renderer precisa
            /// executar.
            void agroup();

            /// Adiciona um comando de desenho ao final do batch.
            ///
            /// @param cmd Comando com estado, intervalos de vértices/índices, textura,
            /// shader e modo de render que serão usados pelo renderer.
            void append(const DDGLDrawCommand &cmd);

            /// Remove todos os comandos acumulados no batch.
            ///
            /// Use antes de iniciar a montagem de um novo frame ou quando os comandos
            /// atuais não devem mais ser renderizados.
            void clear() { drawCommands.clear(); }

            /// Retorna a lista de comandos de desenho acumulados.
            ///
            /// @return Referência constante para os comandos internos. A referência é
            /// válida enquanto o DDGLDrawBatch existir e não for modificado.
            const std::vector<DDGLDrawCommand> &commands() const { return drawCommands; }
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

        /// Aplica uma transformação 2D diretamente em um quad sem coordenadas UV.
        ///
        /// Cada vértice é transformado em torno de `transform.origin`, seguindo a ordem:
        /// escala, skew, rotação e translação. A transformação altera o vetor recebido.
        ///
        /// @param transform Posição, escala, origem, rotação e skew usados no cálculo.
        /// `rotation`, `skewX` e `skewY` são informados em radianos.
        /// @param quad Vetor de vértices que será modificado in-place.
        void transformQuadV3FC4B(const DDTransform2D &transform, std::vector<DDVertexV3FC4B> &quad);

        /// Aplica uma transformação 2D diretamente nos vértices de um quad texturizado.
        ///
        /// A função preserva UVs, cor, índices e textura; apenas as posições dos vértices
        /// são recalculadas. Ao final, `_pos` é atualizado com a posição do primeiro
        /// vértice, quando houver vértices.
        ///
        /// @param transform Posição, escala, origem, rotação e skew usados no cálculo.
        /// `rotation`, `skewX` e `skewY` são informados em radianos.
        /// @param vertexData Dados do quad que serão modificados in-place.
        /// @param replacePos Quando `false`, transforma usando as posições atuais dos
        /// vértices. Quando `true`, subtrai `vertexData._pos` antes do cálculo e escreve
        /// a nova posição a partir de `transform.position`, útil para reposicionar um
        /// quad já criado em vez de acumular a posição anterior.
        void transformDDVertex(const DDTransform2D &transform, VertexQuadDataTextured &vertexData, bool replacePos = false);
    }
}
