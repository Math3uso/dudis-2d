#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "support/platform_test_context.h"
#include "support/test_paths.h"
#include "dudis2d/graphics/res/imageLoader.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/platform/input/input.h"
#include "dudis2d/platform/input/keyboard.h"
#include "dudis2d/graphics/res/fontLoader.h"

TEST_CASE("ddgl render gl platform context initializes and shuts down", "[platform][ddgl]")
{
    dudis::tests::PlatformTestContext context;
    if (!context.initOpenGLWindow("DDGL Render GL platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    REQUIRE(context.platformWindowRef()->getSize().w == 320);
    REQUIRE(context.platformWindowRef()->getSize().h == 240);

    context.shutdown();
}

TEST_CASE("should be able to draw a quad", "[platform][ddgl]")
{
    dudis::tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    dudis::ddgl::VertexQuadDataTextured quadData;
    quadData.vertices.push_back({100, 100, 0, 0, dudis::Color::Red().packed()});
    quadData.vertices.push_back({200, 100, 1, 0, dudis::Color::Green().packed()});
    quadData.vertices.push_back({200, 200, 1, 1, dudis::Color::Blue().packed()});
    quadData.vertices.push_back({100, 200, 0, 1, dudis::Color::White().packed()});
    quadData.indices.push_back(0);
    quadData.indices.push_back(1);
    quadData.indices.push_back(2);
    quadData.indices.push_back(2);
    quadData.indices.push_back(3);
    quadData.indices.push_back(0);

    quadData.textureId = dudis::ddgl::DD_WHITE_TEXTURE_ID;

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());

        render->submit(quadData);

        render->endFrame();
        platform->swapBuffers();
    }

    render->shutdown();
    platform->shutdown();

    context.shutdown();
}

TEST_CASE("should be able to draw a quad with a texture", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());

    if (imageData == INVALID_IMAGE_DATA)
    {
        SUCCEED("Texture file not found, skipping test.");
        return;
    }

    dudis::tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto samplerConfig = ddgl::DDSampler::uniform(ddgl::SamplerFilter::Nearest, ddgl::SamplerWrap::ClampToEdge);
    auto tex = render->createTexture2D(imageData.data, SizeI(imageData.width, imageData.height), samplerConfig);

    dudis::ddgl::VertexQuadDataTextured quadData;

    //     //      (0.0, 1.0) ───────────────────────── (1.0, 1.0)
    //     //             │           │           │
    //     //             │  PARTE 1  │  PARTE 2  │
    //     //             │           │           │
    //     //  (0.0, 0.5) ├───────────┼───────────┤ (1.0, 0.5)  ◄─── Linha da metade (0.5)
    //     //             │           │           │
    //     //             │  PARTE 3  │  PARTE 4  │
    //     //             │           │           │
    //     //  (0.0, 0.0) ───────────────────────── (1.0, 0.0)
    //     //                         ▲
    //     //                         └─ Linha da metade (0.5)

    //     // U (Eixo Horizontal): Equivale ao eixo X da imagem (anda para a esquerda e para a direita).
    //     // V (Eixo Vertical): Equivale ao eixo Y da imagem (anda para baixo e para cima).

    float u0 = 0.0f;
    float u1 = 0.1f;
    float v0 = 0.0f;
    float v1 = 1.0f;

    // // flipx
    // std::swap(u0, u1);

    quadData.vertices.push_back({100, 100, u0, v0, dudis::Color::Red().packed()});
    quadData.vertices.push_back({200, 100, u1, v0, dudis::Color::Green().packed()});
    quadData.vertices.push_back({200, 200, u1, v1, dudis::Color::Blue().packed()});
    quadData.vertices.push_back({100, 200, u0, v1, dudis::Color::White().packed()});
    quadData.indices.push_back(0);
    quadData.indices.push_back(1);
    quadData.indices.push_back(2);
    quadData.indices.push_back(2);
    quadData.indices.push_back(3);
    quadData.indices.push_back(0);

    quadData.textureId = tex.id;

    dudis::Vec2 pos = {0, 0};
    float rotation = 0.f;

    auto platform = context.platformWindowRef();

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());
        render->submit(quadData);

        render->endFrame();
        platform->swapBuffers();
    }

    render->shutdown();
    platform->shutdown();
    context.shutdown();

    ImageLoader::freeImageData(imageData);

    REQUIRE(imageData == INVALID_IMAGE_DATA);
}

TEST_CASE("should be able to draw a texture with uv in pixels", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());

    if (imageData == INVALID_IMAGE_DATA)
    {
        SUCCEED("Texture file not found, skipping test.");
        return;
    }

    dudis::tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto tex = render->createTexture2D(imageData.data, SizeI(imageData.width, imageData.height));

    auto quadData = ddgl::createQuadData(SizeF(50, 50), Vec2(50, 50), Rect{0, 0, 32, 32}, 0xFF0000FF, tex);

    auto platform = context.platformWindowRef();

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());
        render->submit(quadData);

        render->endFrame();
        platform->swapBuffers();
    }

    render->shutdown();
    platform->shutdown();
    context.shutdown();

    ImageLoader::freeImageData(imageData);

    REQUIRE(imageData == INVALID_IMAGE_DATA);
}

TEST_CASE("should be able to transform a quad", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());

    if (imageData == INVALID_IMAGE_DATA)
    {
        SUCCEED("Texture file not found, skipping test.");
        return;
    }

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto tex = render->createTexture2D(imageData.data, SizeI(imageData.width, imageData.height));

    auto baseQuadData = ddgl::createQuadData(SizeF(50, 50), Vec2(50, 50), Rect{0, 0, 32, 32}, 0xFFFFFFFF, tex);

    auto platform = context.platformWindowRef();
    float time = 0.f;

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());

        time += 1.f / 60.f;
        float pingPong = (std::sin(time * 2.f) + 1.f) * 0.5f;
        float offsetX = -40.f + pingPong * 80.f;
        float scale = 0.9f + pingPong * 0.2f;

        ddgl::DDTransform2D transform;
        transform.position = Vec2(offsetX, 0.f);
        transform.origin = Vec2(75.f, 75.f);
        transform.rotation = time * 2.f;
        transform.scale = Vec2(scale, scale);
        // transform.skewX = std::sin(time) * 0.5f;
        // transform.skewY = std::cos(time) * 0.5f;

        auto quadData = baseQuadData;
        ddgl::transformDDVertex(transform, quadData);
        render->submit(quadData);

        render->endFrame();
        platform->swapBuffers();
    }

    render->shutdown();
    platform->shutdown();
    context.shutdown();

    ImageLoader::freeImageData(imageData);

    REQUIRE(imageData == INVALID_IMAGE_DATA);
}

TEST_CASE("should be able to create and draw a framebuffer", "[platform][ddgl]")
{

    using namespace dudis;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto baseQuadData = ddgl::createQuadData(SizeF(100, 100), Vec2(50, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFFFFFFFF, ddgl::DD_WHITE_TEXTURE);
    auto quadChild = ddgl::createQuadData(SizeF(50, 50), Vec2(25, 25), ddgl::DD_NONE_TEXTURE_RECT, 0xFFFF0000, ddgl::DD_WHITE_TEXTURE);

    auto frameBuffer = render->createFrameBuffer(baseQuadData);
    auto platform = context.platformWindowRef();

    REQUIRE(frameBuffer.id != ddgl::DD_INVALID_FRAMEBUFFER.id);

    while (platform->isOpen())
    {
        platform->eventListener();

        render->bindFrameBuffer(frameBuffer);
        render->clear(Color::Green());
        render->submit(quadChild);
        render->unbindFrameBuffer();

        render->beginFrame();
        render->clear(Color::Default());

        render->submit(baseQuadData);

        render->endFrame();

        platform->swapBuffers();
    }

    render->deleteFrameBuffer(frameBuffer);
    render->shutdown();
    platform->shutdown();
    context.shutdown();
}

TEST_CASE("drawCallCount test", "[platform][ddgl]")
{
    using namespace dudis;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(800, 600)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();

    auto quad1 = ddgl::createQuadData(SizeF(100, 100), Vec2(50, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFFFF0000, ddgl::DD_WHITE_TEXTURE);
    auto quad2 = ddgl::createQuadData(SizeF(100, 100), Vec2(200, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFF00FF00, ddgl::DD_WHITE_TEXTURE);

    int lastDrawCallCount = 0;

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());

        render->submit(quad1);
        render->submit(quad2);

        render->endFrame();

        if (lastDrawCallCount == 0)
        {
            lastDrawCallCount = render->getDrawCallCount();
        }
        // std::cout << "Draw calls this frame: " << render->getDrawCallCount() << std::endl;

        platform->swapBuffers();
    }

    REQUIRE(lastDrawCallCount == 1);

    render->shutdown();
    platform->shutdown();
    context.shutdown();
}

TEST_CASE("drawCallCount test 2", "[platform][ddgl]")
{
    using namespace dudis;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(800, 600)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();

    auto imgData = ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());

    auto tex = render->createTexture2D(imgData.data, SizeI(imgData.width, imgData.height));

    auto quad1 = ddgl::createQuadData(SizeF(100, 100), Vec2(50, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFFFF0000, ddgl::DD_WHITE_TEXTURE);
    auto quad2 = ddgl::createQuadData(SizeF(100, 100), Vec2(200, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFF00FF00, ddgl::DD_WHITE_TEXTURE);

    auto quad3 = ddgl::createQuadData(SizeF(100, 100), Vec2(350, 50), DDRect{0, 0, 32, 32}, 0xFFFFFFFF, tex);

    int lastDrawCallCount = 0;

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());

        render->submit(quad1);
        render->submit(quad2);
        render->submit(quad3);
        render->endFrame();

        if (lastDrawCallCount == 0)
        {
            lastDrawCallCount = render->getDrawCallCount();
        }

        platform->swapBuffers();
    }

    REQUIRE(lastDrawCallCount == 2);

    render->shutdown();
    platform->shutdown();
    context.shutdown();
}

TEST_CASE("sem nome por enquanto", "[platform][ddgl]")
{
    using namespace dudis;
    using namespace ddgl;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(800, 600)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto imgData = ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());
    auto bg = ImageLoader::loadFromFile(tests::assetPath("bg01.png").string().c_str());

    if (imgData == INVALID_IMAGE_DATA || bg == INVALID_IMAGE_DATA)
    {
        SUCCEED("Texture file not found, skipping test.");
        return;
    }

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();

    DDTextureSampler samplerConfig1 = DDSampler::uniform(SamplerFilter::Nearest, SamplerWrap::ClampToEdge);
    DDTextureSampler samplerConfig2 = DDSampler::uniform(SamplerFilter::Linear, SamplerWrap::ClampToEdge);
    DDTextureSampler samplerConfig3 = DDSampler::uniform(SamplerFilter::Nearest, SamplerWrap::Repeat);

    auto tex = render->createTexture2D(imgData.data, SizeI(imgData.width, imgData.height), samplerConfig1);
    auto tex2 = render->createTexture2D(imgData.data, SizeI(imgData.width, imgData.height), samplerConfig2);
    auto tex3 = render->createTexture2D(bg.data, SizeI(bg.width, bg.height), samplerConfig3);

    // usando filter Nearest
    auto quad1 = ddgl::createQuadData(SizeF(100, 100), Vec2(50, 50), DDRect{0, 0, 32, 32}, 0xFFFFFFFF, tex);

    auto quad2 = ddgl::createQuadData(SizeF(100, 100), Vec2(200, 50), DDRect{0, 0, 32, 32}, 0xFFFFFFFF, tex2);

    auto quad3 = ddgl::createQuadData(SizeF(64 * 3, 64 * 3), Vec2(300, 150), DDRect{0, 0, 64 * 3, 64 * 3}, 0xFFFFFFFF, tex3);

    while (platform->isOpen())
    {
        platform->eventListener();
        render->beginFrame();
        render->clear(dudis::Color::Default());

        render->submit(quad3);
        render->submit(quad1);
        render->submit(quad2);

        render->endFrame();

        platform->swapBuffers();
    }

    render->deleteTexture2D(tex);
    render->deleteTexture2D(tex2);
    render->shutdown();
    platform->shutdown();
    context.shutdown();
    ImageLoader::freeImageData(imgData);
    ImageLoader::freeImageData(bg);
}

TEST_CASE("should be able to use scissor test", "[platform][ddgl]")
{
    using namespace dudis;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(800, 600)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();

    auto quad = ddgl::createQuadData(SizeF(400, 400), Vec2(50, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFFFF0000, ddgl::DD_WHITE_TEXTURE);
    auto quad2 = ddgl::createQuadData(SizeF(50, 50), Vec2(40, 50), ddgl::DD_NONE_TEXTURE_RECT, 0xFF00FF00, ddgl::DD_WHITE_TEXTURE);

    ddgl::DDTransform2D transform;
    transform.origin = Vec2(0, 0);
    transform.position = Vec2(50, 50);
    transform.rotation = 0.f;
    transform.scale = Vec2(1.f, 1.f);

    while (platform->isOpen())
    {
        platform->eventListener();
        Input::update();

        if (Keyboard::isDown(KeyCode::A))
        {
            transform.position.x -= 1.f;
        }
        else if (Keyboard::isDown(KeyCode::D))
        {
            transform.position.x += 1.f;
        }
        else if (Keyboard::isDown(KeyCode::W))
        {
            transform.position.y -= 1.f;
        }
        else if (Keyboard::isDown(KeyCode::S))
        {
            transform.position.y += 1.f;
        }

        render->beginFrame();
        render->clear(dudis::Color::Default());

        render->submit(quad);
        int frameBufferH = platform->getSize().h;

        // corrige origim
        DDRect scissorRect = DDRect(50, frameBufferH - (50 + 400), 400, 400);

        render->bindScissor(scissorRect);
        ddgl::transformDDVertex(transform, quad2, ddgl::DD_REPLACE_POS);
        render->submit(quad2);
        render->unbindScissor();

        render->endFrame();

        platform->swapBuffers();
    }

    render->shutdown();
    platform->shutdown();
    context.shutdown();
}

TEST_CASE("should be able to load TTF in memory", "[platform][ddgl]")
{
    using namespace dudis;
    // ImageLoader::loadFromFile(tests::assetPath("player.png").string().c_str());
    auto data = dudis::FontLoader::loadTTF(tests::assetPath("font.ttf").string().c_str());
}

TEST_CASE("teste temp", "[platform][ddgl]")
{
    using namespace dudis;

    tests::PlatformTestContext context;

    if (!context.initOpenGLWindow("DDGL Render GL platform test", SizeI(800, 600)))
    {
        SUCCEED("No graphical display is available for platform ddgl render gl tests.");
        return;
    }

    auto render = context.renderRef();

    auto platform = context.platformWindowRef();
    platform->setFPSLimit(0);

    const int quadCount = 100;
    const SizeF quadSize(50.f, 50.f);
    const SizeI windowSize = platform->getSize();

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> xDist(0.f, static_cast<float>(windowSize.w) - quadSize.w);
    std::uniform_real_distribution<float> yDist(0.f, static_cast<float>(windowSize.h) - quadSize.h);
    std::uniform_int_distribution<int> colorDist(0, 255);

    std::vector<ddgl::VertexQuadDataTextured> quads;
    quads.reserve(quadCount);

    float fpsTimer = 0.f;
    int frames = 0;

    for (int i = 0; i < quadCount; ++i)
    {
        const Vec2 pos(xDist(rng), yDist(rng));
        const uint32_t color = Color(
                                   static_cast<uint8_t>(colorDist(rng)),
                                   static_cast<uint8_t>(colorDist(rng)),
                                   static_cast<uint8_t>(colorDist(rng)),
                                   255)
                                   .packed();

        quads.push_back(ddgl::createQuadData(quadSize, pos, ddgl::DD_NONE_TEXTURE_RECT, color, ddgl::DD_WHITE_TEXTURE));
    }

    while (platform->isOpen())
    {
        platform->eventListener();

        render->beginFrame();
        render->clear(dudis::Color::Default());

        for (const auto &quad : quads)
        {
            render->submit(quad);
        }

        render->endFrame();

        platform->swapBuffers();

        fpsTimer += platform->getFrameTime();
        frames++;

        if (fpsTimer >= 1.f)
        {
            std::cout << "FPS: " << frames / fpsTimer
                      << " | draw calls: " << render->getDrawCallCount()
                      << " | quads: " << quadCount
                      << "\n";

            fpsTimer = 0.f;
            frames = 0;
        }
    }

    render->shutdown();
    platform->shutdown();
    context.shutdown();
}
