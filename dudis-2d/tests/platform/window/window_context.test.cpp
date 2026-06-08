#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <thread>

#include "support/platform_test_context.h"

TEST_CASE("window platform context initializes and shuts down", "[platform][window]")
{
    dudis::tests::PlatformTestContext context;
    if (!context.initOpenGLWindow("Window platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform window tests.");
        return;
    }

    REQUIRE(context.platformWindowRef()->getSize().w == 320);
    REQUIRE(context.platformWindowRef()->getSize().h == 240);

    context.shutdown();
}

TEST_CASE("window platform context updates frame delta time", "[platform][window]")
{
    dudis::tests::PlatformTestContext context;
    if (!context.initOpenGLWindow("Window delta time test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform window tests.");
        return;
    }

    auto *window = context.platformWindowRef();

    REQUIRE(window->getFrameTime() == 0.0f);

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    window->swapBuffers();

    const float deltaTime = window->getFrameTime();

    REQUIRE(deltaTime > 0.0f);
    REQUIRE(deltaTime <= 0.25f);

    context.shutdown();
}
