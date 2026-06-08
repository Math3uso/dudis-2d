#include <iostream>
#include "dudis2d/graphics/ddgl/render/renderGL.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/graphics/ddgl/color.h"
#include "SDL3/SDL.h"
#include <glad/glad.h>

using namespace dudis;
using namespace ddgl;

namespace
{
    GLenum toGLFilter(SamplerFilter filter)
    {
        switch (filter)
        {
        case SamplerFilter::Nearest:
            return GL_NEAREST;
        case SamplerFilter::Linear:
            return GL_LINEAR;
        default:
            return GL_LINEAR;
        }
    }

    GLenum toGLWrap(SamplerWrap wrap)
    {
        switch (wrap)
        {
        case SamplerWrap::Repeat:
            return GL_REPEAT;
        case SamplerWrap::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        default:
            return GL_REPEAT;
        }
    }
}

bool RenderGL::_checkShader(unsigned int shader, unsigned int type)
{
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
        return true;

    GLint length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    std::string log;
    log.resize(length > 1 ? length : 1);

    glGetShaderInfoLog(shader, length, nullptr, log.data());

    const char *typeStr = "Unknown";
    if (type == GL_VERTEX_SHADER)
        typeStr = "Vertex";
    if (type == GL_FRAGMENT_SHADER)
        typeStr = "Fragment";

    std::cerr << "[Shader Error - " << typeStr << "]\n"
              << log << '\n';

    return false;
};

bool RenderGL::_createShaderProgramDefault(QuadShaderType type)
{
    // quad sem texturas
    ShaderHandle vertShader;
    ShaderHandle fragShader;

    vertShader.type = ShaderType::VERT;
    fragShader.type = ShaderType::FRAG;

    // shaders para quad com textura

    vertShader.src = R"glsl(
        #version 330 core

        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec2 aTexCoord;

        uniform mat4 uProjection;
        uniform mat4 uView;

        out vec4 fragColor;
        out vec2 texCoord;

        void main(){
            gl_Position = uProjection * uView * vec4(aPos, 0.0f,1.0f);
            fragColor = aColor;
            texCoord = aTexCoord;
        }
    )glsl";

    fragShader.src = R"glsl(
        #version 330 core

        in vec4 fragColor;
        in vec2 texCoord;

        uniform sampler2D uTexture;

        out vec4 finalColor;

        void main(){
            finalColor = texture(uTexture, texCoord) * fragColor;
        }
    )glsl";

    vertShader.shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader.shader, 1, &vertShader.src, nullptr);

    fragShader.shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader.shader, 1, &fragShader.src, nullptr);

    glCompileShader(vertShader.shader);
    glCompileShader(fragShader.shader);

    if (!_checkShader(vertShader.shader, GL_VERTEX_SHADER) || !_checkShader(fragShader.shader, GL_FRAGMENT_SHADER))
    {
        return false;
    }

    _shaderProgram = glCreateProgram();

    glAttachShader(_shaderProgram, vertShader.shader);
    glAttachShader(_shaderProgram, fragShader.shader);

    glLinkProgram(_shaderProgram);

    glDeleteShader(vertShader.shader);
    glDeleteShader(fragShader.shader);

    int success = 0;
    glGetProgramiv(_shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint length = 0;
        glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &length);

        std::string log;
        log.resize(length > 1 ? length : 1);

        glGetProgramInfoLog(_shaderProgram, length, nullptr, log.data());
    }

    return true;
}

bool RenderGL::init()
{

    DDRenderDevice::init();

    PlatformWindow *window = App::_getPlatformWindow();

    if (window && !window->isReady())
    {
        std::cerr << "Erro no RenderGL: Janela nao esta pronta. Detalhes SDL: " << std::endl;
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Erro no RenderGL: falha ao carregar funcoes OpenGL via GLAD." << std::endl;
        return false;
    }

    SizeI wSize = window->getSize();

    glViewport(0, 0, wSize.w, wSize.h);

    if (!this->_createShaderProgramDefault())
    {
        return false;
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    // vertex sem textura

    // Apos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DDVertex_V3F_C4B_U2F), (void *)0);

    // aColor
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DDVertex_V3F_C4B_U2F), (void *)offsetof(DDVertex_V3F_C4B_U2F, color));

    // aTexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(DDVertex_V3F_C4B_U2F), (void *)offsetof(DDVertex_V3F_C4B_U2F, u));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, DD_MAX_VERTEX * sizeof(DDVertex_V3F_C4B_U2F), nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, DD_MAX_INDEX * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

    this->_vertRect.reserve(DD_MAX_VERTEX);
    this->_index.reserve(DD_MAX_INDEX);

    if (_projectionType == ProjectionType::ORTHOGRAPHIC)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        _projection = glm::ortho(0.0f, static_cast<float>(wSize.w), static_cast<float>(wSize.h), 0.0f, -1.0f, 1.0f);
        _view = glm::mat4(1.0f);

        glUseProgram(_shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(_projection));
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, "uView"), 1, GL_FALSE, glm::value_ptr(_view));
        std::cout << "Projection and view matrices set for orthographic mode." << std::endl;
    }

    // Cria textura branca 1x1 para renderizar quads sem textura
    uint32_t whitePixel = 0xFFFFFFFF;
    _whiteTexture = this->createTexture2D(&whitePixel, SizeI(1, 1));
    _index = std::vector<uint32_t>{0, 1, 2, 2, 3, 0}; // indices para um quad;

    return true;
}

int RenderGL::getDrawCallCount() const
{
    return _drawCallCount;
}

void RenderGL::beginFrame()
{
    Vec4 color = _clearColor.normalized();
    _drawCallCount = 0;

    if (_viewPortDefault != DDRECT_NONE)
    {
        glViewport(static_cast<int>(_viewPortDefault.x), static_cast<int>(_viewPortDefault.y), static_cast<int>(_viewPortDefault.w), static_cast<int>(_viewPortDefault.h));
    }
    else
    {
        SizeI wSize = App::_getPlatformWindow()->getSize();
        glViewport(0, 0, wSize.w, wSize.h);
    }

    // glViewport(0, 0, App::getWindowSize().w, App::getWindowSize().h);
    // glClearColor(color.x, color.y, color.z, color.w);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderGL::endFrame()
{
    this->flush();
}

void RenderGL::submitRect(const VertexQuadData &data)
{
    // Caso onde n ocorre o batch, entao renderiza imediatamente
    if (data.vertices.size() > DD_MAX_VERTEX || data.indices.size() > DD_MAX_INDEX)
    {
        // flush do batch atual
        this->flush();
        return;
    }

    // Caso onde o batch atual + nova data excede o limite, entao flush do batch atual e depois adiciona nova data
    if (_vertRect.size() + data.vertices.size() > DD_MAX_VERTEX || _index.size() + data.indices.size() > DD_MAX_INDEX)
    {
        this->flush();
    }

    // Adiciona nova data ao batch
    _vertRect.insert(_vertRect.end(), data.vertices.begin(), data.vertices.end());
    _index.insert(_index.end(), data.indices.begin(), data.indices.end());

    DDGLDrawCommand cmd;
    cmd.startVertex = _vertRect.size() - data.vertices.size();
    cmd.vertexCount = data.vertices.size();
    cmd.startIndex = _index.size() - data.indices.size();
    cmd.indexCount = data.indices.size();
    cmd.textureId = DD_WHITE_TEXTURE_ID;

    _drawCommands.append(cmd);
}

void RenderGL::submit(const VertexQuadDataTextured &data)
{

    // Caso onde n ocorre o batch, entao renderiza imediatamente
    if (data.vertices.size() > DD_MAX_VERTEX || data.indices.size() > DD_MAX_INDEX)
    {
        // flush do batch atual
        this->flush();
        return;
    }

    // Caso onde o batch atual + nova data excede o limite, entao flush do batch atual e depois adiciona nova data
    if (_vert.size() + data.vertices.size() > DD_MAX_VERTEX || _index.size() + data.indices.size() > DD_MAX_INDEX)
    {
        this->flush();
    }

    const uint32_t vertexOffset = static_cast<uint32_t>(_vert.size());

    // primeiro adiciona nova data ao batch, depois cria comando de draw para essa data
    this->_vert.insert(_vert.end(), data.vertices.begin(), data.vertices.end());
    //    _index.insert(_index.end(), data.indices.begin(), data.indices.end());

    for (uint32_t index : data.indices)
    {
        _index.push_back(vertexOffset + index);
    }

    DDGLDrawCommand cmd;
    cmd.startVertex = _vert.size() - data.vertices.size();
    cmd.vertexCount = data.vertices.size();
    cmd.startIndex = _index.size() - data.indices.size();
    cmd.indexCount = data.indices.size();
    cmd.textureId = data.textureId == DD_WHITE_TEXTURE_ID ? _whiteTexture.id : data.textureId;
    cmd.programShader = data.programShader == DD_PROGRAM_DEFAULT ? _shaderProgram : data.programShader;
    cmd.state = PilelineState::Draw;

    //   _drawCommands.push_back(cmd);
    _drawCommands.append(cmd);
}

void RenderGL::bindScissor(const DDRect &rect)
{
    DDGLDrawCommand cmd;
    cmd.state = PilelineState::Scissor;
    cmd.scissorRect = rect;
    _drawCommands.append(cmd);
    // glEnable(GL_SCISSOR_TEST);
    // glScissor(static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.w), static_cast<int>(rect.h));
}

void RenderGL::unbindScissor()
{
    DDGLDrawCommand cmd;
    cmd.state = PilelineState::EndScissor;
    cmd.scissorRect = DDRECT_NONE;
    _drawCommands.append(cmd);
    // glDisable(GL_SCISSOR_TEST);
}

void RenderGL::flush()
{
    // Se nao tiver nada para renderizar, retorna
    if (_drawCommands.commands().empty())
    {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _vert.size() * sizeof(DDVertex_V3F_C4B_U2F), _vert.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _index.size() * sizeof(uint32_t), _index.data());

    glUseProgram(_shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(_shaderProgram, "uTexture"), 0);

    glBindVertexArray(_vao);

    int total = _vert.size() / 4; // cada quad tem 4 vertices, entao total de quads é vert.size() / 4
    int i = 0;

    // Agrupa comandos de draw por textura e shader para minimizar bind calls
    if (_drawCommands.commands().size() > 0)
    {
        // std::cout << "Draw commands before grouping: " << _drawCommands.commands().size() << std::endl;
        _drawCommands.agroup();
        // std::cout << "Draw commands after grouping: " << _drawCommands.commands().size() << std::endl;
    }

    for (const auto &cmd : _drawCommands.commands())
    {
        switch (cmd.state)
        {
        case PilelineState::Scissor:
            glScissor(cmd.scissorRect.x, cmd.scissorRect.y, cmd.scissorRect.w, cmd.scissorRect.h);
            glEnable(GL_SCISSOR_TEST);
            break;
        case PilelineState::EndScissor:
            glDisable(GL_SCISSOR_TEST);
            break;
        case PilelineState::Draw:
            i++;
            glBindTexture(GL_TEXTURE_2D, cmd.textureId);
            // glDrawElementsBaseVertex(
            //     GL_TRIANGLES,
            //     cmd.indexCount,
            //     GL_UNSIGNED_INT,
            //     (void *)(cmd.startIndex * sizeof(uint32_t)),
            //     cmd.startVertex

            //     //
            // );
            _drawCallCount++;
            glDrawElements(
                GL_TRIANGLES,
                cmd.indexCount,
                GL_UNSIGNED_INT,
                (void *)(cmd.startIndex * sizeof(uint32_t))
                //
            );
            break;
        default:
            break;
        }
    }

    // Limpa batch
    _vertRect.clear();
    _vert.clear();
    _index.clear();
    _drawCommands.clear();
}

void RenderGL::clearColor(const Color &color)
{
    _clearColor = color;
}

void RenderGL::clear(const Color &color)
{
    if (_clearColor != color)
    {
        _clearColor = color;
    }
    glClearColor(_clearColor.normalized().x, _clearColor.normalized().y, _clearColor.normalized().z, _clearColor.normalized().w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

DDTexture2D RenderGL::createTexture2D(const void *data, SizeI size, DDTextureSampler sampler)
{
    TextureHandle texture;

    texture.width = size.w;
    texture.height = size.h;
    texture.mipLevels = 1;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.w, size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Gerar mipmaps apenas se houver dados fornecidos, para evitar overhead desnecessário ao criar texturas vazias (como as usadas para framebuffers)
    if (data)
        glGenerateMipmap(GL_TEXTURE_2D);

    // temp
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Configura os parâmetros de filtragem e repetição com base no sampler fornecido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLFilter(sampler.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLFilter(sampler.magFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLWrap(sampler.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLWrap(sampler.wrapT));

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void RenderGL::deleteTexture2D(const DDTexture2D &texture)
{
    if (texture.id != 0)
    {
        glDeleteTextures(1, &texture.id);
        std::cout << "Deleted texture with ID: " << texture.id << std::endl;
    }
}

FrameBuffer RenderGL::createFrameBuffer(VertexQuadDataTextured &data)
{
    FrameBuffer frameBuffer;

    glGenFramebuffers(1, &frameBuffer.id);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.id);

    auto samplerConfig = DDTextureSampler::uniform(SamplerFilter::Linear, SamplerWrap::ClampToEdge);

    std::cout << "Creating framebuffer with size: " << data._size.w << "x" << data._size.h << " and texture ID: " << data.textureId << std::endl;

    auto texture = this->createTexture2D(nullptr, SizeI(data._size.w, data._size.h), samplerConfig);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Erro ao criar framebuffer: status incompleto." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        this->deleteTexture2D(texture);
        glDeleteFramebuffers(1, &frameBuffer.id);
        return DD_INVALID_FRAMEBUFFER;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    frameBuffer.width = data._size.w;
    frameBuffer.height = data._size.h;
    frameBuffer.texture = texture;
    data.textureId = texture.id;
    return frameBuffer;
}

void RenderGL::bindFrameBuffer(const FrameBuffer &frameBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.id);
    glViewport(0, 0, frameBuffer.width, frameBuffer.height);
}

void RenderGL::unbindFrameBuffer()
{
    this->flush();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderGL::deleteFrameBuffer(const FrameBuffer &frameBuffer)
{
    if (frameBuffer.id != 0)
    {
        this->deleteTexture2D(frameBuffer.texture);
        glDeleteFramebuffers(1, &frameBuffer.id);
        std::cout << "[INFO] Deleted framebuffer with ID: " << frameBuffer.id << std::endl;
    }
}

void RenderGL::shutdown()
{

    // puts("[INFO] shutdown in RENDERGL");

    this->deleteTexture2D(_whiteTexture);

    glDeleteProgram(_shaderProgram);
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);

    _vao = 0;
    _vbo = 0;
    _ebo = 0;
    _shaderProgram = 0;

    _vertRect.clear();
    _index.clear();
}
