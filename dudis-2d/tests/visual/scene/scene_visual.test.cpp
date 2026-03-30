#include <catch2/catch_test_macros.hpp>

#include "support/test_context.h"
#include "support/visual_check.h"

TEST_CASE("scene render keeps expected colors on screen", "[visual]")
{
    dudis::tests::TestContext context;
    if (!context.init())
    {
        SKIP("No graphical display is available for visual tests.");
    }

    context.pushScene(dudis::tests::makeScene());
    context.windowRef().SetClearColor(dudis::Color::Hex(0x202020FF));
    context.pushDrawable(dudis::tests::makeQuadDefault());
    context.runFrames(3);

    auto screenshot = dudis::tests::captureScreen();
    REQUIRE(dudis::tests::exportImageArtifact(screenshot, "scene_visual.png"));

    const auto background = dudis::tests::samplePixel(screenshot, 10, 10);
    const auto rectangle = dudis::tests::samplePixel(screenshot, 320, 220);

    CHECK(dudis::tests::colorNear(background, dudis::Color::Hex(0x202020FF), 4));
    CHECK(dudis::tests::colorNear(rectangle, dudis::Color::White(), 12));

    dudis::tests::unloadImage(screenshot);
    context.shutdown();
}
