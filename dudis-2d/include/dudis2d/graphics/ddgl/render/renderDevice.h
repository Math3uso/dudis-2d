#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "dudis2d/graphics/ddgl/ddglTypes.h"
#include "dudis2d/graphics/color.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/core/utils/sizeI.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace dudis
{
    namespace ddgl
    {

        enum class ProjectionType
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        class DDRenderDevice
        {
        protected:
            std::vector<DDVertex_V3F_C4B_U2F> _vert;
            std::vector<DDVertexV3FC4B> _vertRect;
            std::vector<uint32_t> _index;
            // std::vector<DDGLDrawCommand> _drawCommands;
            DDGLDrawBatch _drawCommands;
            DDRect _viewPortDefault = DDRECT_NONE;
            ProjectionType _projectionType;
            glm::mat4 _projection;
            glm::mat4 _view;
            int _drawCallCount = 0;

        public:
            virtual bool init();
            virtual void shutdown() = 0;
            virtual void beginFrame() = 0;
            virtual void submit(const VertexQuadDataTextured &data, RenderMode mode = RenderMode::Texture) = 0;
            virtual void submitRect(const VertexQuadData &data) = 0;
            virtual void flush() = 0;
            virtual void endFrame() = 0;
            virtual DDTexture2D createTexture2D(const void *data, SizeI size, DDTextureSampler sampler = DDTextureSampler(), TexInternalFormat format = TexInternalFormat::RGBA()) = 0;
            virtual void deleteTexture2D(const DDTexture2D &texture) = 0;
            virtual void clearColor(const Color &color) = 0;
            virtual void clear(const Color &color) = 0;
            virtual void setProjectionType(ProjectionType type) { _projectionType = type; };
            virtual ProjectionType getProjectionType() const { return _projectionType; };
            virtual void setViewPort(const DDRect &port) { _viewPortDefault = port; };
            // virtual FrameBuffer createFrameBuffer(int width, int height) = 0;
            virtual FrameBuffer createFrameBuffer(VertexQuadDataTextured &data) = 0;
            virtual void deleteFrameBuffer(const FrameBuffer &frameBuffer) = 0;
            virtual void bindFrameBuffer(const FrameBuffer &frameBuffer) = 0;
            virtual void unbindFrameBuffer() = 0;

            virtual void bindScissor(const DDRect &rect) = 0;
            virtual void unbindScissor() = 0;

            virtual int getDrawCallCount() const { return _drawCallCount; }
            // virtual void submitFrameBuffer(const FrameBuffer &frameBuffer) = 0;
            //  virtual void bindFrameBuffer(const FrameBuffer &frameBuffer) = 0;
            //  virtual void unbindFrameBuffer() = 0;

            template <typename T>
            static std::shared_ptr<T> create()
            {
                static_assert(std::is_base_of_v<DDRenderDevice, T>,
                              "T precisa herdar de DDRenderDevice");

                static_assert(!std::is_abstract_v<T>,
                              "T nao pode ser uma classe abstrata");

                return std::make_shared<T>();
            }
        };
    }
}
