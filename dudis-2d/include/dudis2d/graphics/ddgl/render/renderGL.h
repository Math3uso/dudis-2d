#pragma once

#include "dudis2d/graphics/ddgl/render/renderDevice.h"

namespace dudis
{
    namespace ddgl
    {

        enum class QuadShaderType
        {
            DEFAULT,
            TEXTURED
        };

        class RenderGL : public DDRenderDevice
        {
        private:
            uint32_t _shaderProgram = 0;
            uint32_t _vao = 0;
            uint32_t _vbo = 0;
            uint32_t _ebo = 0;
            TextureHandle _whiteTexture = {0};
            Color _clearColor = Color(31, 31, 31, 255);
            bool _checkShader(unsigned int shader, unsigned int type);
            bool _createShaderProgramDefault(QuadShaderType type = QuadShaderType::DEFAULT);

        public:
            virtual bool init() override;
            virtual void shutdown() override;
            virtual void beginFrame() override;
            virtual void submit(const VertexQuadDataTextured &data, RenderMode mode = RenderMode::Texture) override;
            virtual void submitRect(const VertexQuadData &data) override;
            virtual void flush() override;
            virtual void endFrame() override;
            virtual DDTexture2D createTexture2D(const void *data, SizeI size, DDTextureSampler sampler = DDTextureSampler(), TexInternalFormat format = TexInternalFormat::RGBA()) override;
            virtual void deleteTexture2D(const DDTexture2D &texture) override;
            virtual void clearColor(const Color &color) override;
            virtual void clear(const Color &color) override;
            // virtual FrameBuffer createFrameBuffer(int width, int height) override;
            virtual FrameBuffer createFrameBuffer(VertexQuadDataTextured &data) override;
            virtual void deleteFrameBuffer(const FrameBuffer &frameBuffer) override;
            virtual void bindFrameBuffer(const FrameBuffer &frameBuffer) override;
            virtual void unbindFrameBuffer() override;

            virtual void bindScissor(const DDRect &rect) override;
            virtual void unbindScissor() override;

            virtual int getDrawCallCount() const override;
        };
    }
}
