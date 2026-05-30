#include <catch2/catch_test_macros.hpp>

#include "support/test_context.h"

TEST_CASE("scene can be created and pushed", "[smoke]")
{
    dudis::tests::TestContext context;
    if (!context.init())
    {
        SUCCEED("No graphical display is available for smoke tests.");
        return;
    }

    auto scene = dudis::tests::makeScene();
    REQUIRE(scene != nullptr);

    context.pushScene(std::move(scene));
    context.runFrames(1);
    context.shutdown();
}

TEST_CASE("scene runs with a rectangle", "[smoke]")
{
    dudis::tests::TestContext context;
    if (!context.init())
    {
        SUCCEED("No graphical display is available for smoke tests.");
        return;
    }

    context.pushScene(dudis::tests::makeScene());
    context.windowRef().SetClearColor(dudis::Color::Hex(0x202020FF));
    context.pushDrawable(dudis::tests::makeQuadDefault());

    context.runFrames(30);
    context.shutdown();
}

TEST_CASE("scene runs with a sprite asset", "[smoke]")
{
    dudis::tests::TestContext context;
    if (!context.init())
    {
        SUCCEED("No graphical display is available for smoke tests.");
        return;
    }

    context.pushScene(dudis::tests::makeScene());
    context.windowRef().SetClearColor(dudis::Color::Hex(0x202020FF));
    context.pushDrawable(dudis::tests::makePlayerSprite());

    context.runFrames(30);
    context.shutdown();
}
