#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "support/platform_test_context.h"
#include "dudis2d/graphics/res/imageLoader.h"
#include "dudis2d/core/math/rect.h"

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

    platform->shutdown();
    render->shutdown();

    //    context.shutdown();
}

TEST_CASE("should be able to draw a quad with a texture", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile("assets/player.png");

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

    //      (0.0, 1.0) ───────────────────────── (1.0, 1.0)
    //             │           │           │
    //             │  PARTE 1  │  PARTE 2  │
    //             │           │           │
    //  (0.0, 0.5) ├───────────┼───────────┤ (1.0, 0.5)  ◄─── Linha da metade (0.5)
    //             │           │           │
    //             │  PARTE 3  │  PARTE 4  │
    //             │           │           │
    //  (0.0, 0.0) ───────────────────────── (1.0, 0.0)
    //                         ▲
    //                         └─ Linha da metade (0.5)

    // U (Eixo Horizontal): Equivale ao eixo X da imagem (anda para a esquerda e para a direita).
    // V (Eixo Vertical): Equivale ao eixo Y da imagem (anda para baixo e para cima).

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

    platform->shutdown();
    render->shutdown();
    ImageLoader::freeImageData(imageData);

    REQUIRE(imageData == INVALID_IMAGE_DATA);
}

TEST_CASE("should be able to draw a texture with uv in pixels", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile("assets/player.png");

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

    platform->shutdown();
    render->shutdown();
    ImageLoader::freeImageData(imageData);

    REQUIRE(imageData == INVALID_IMAGE_DATA);
}

TEST_CASE("should be able to transform a quad", "[platform][ddgl]")
{
    using namespace dudis;

    auto imageData = ImageLoader::loadFromFile("assets/player.png");

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

    platform->shutdown();
    render->shutdown();
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
    platform->shutdown();
    render->shutdown();
}