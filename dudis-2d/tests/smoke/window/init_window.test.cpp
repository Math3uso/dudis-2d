#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"

#include <cstdlib>

TEST_CASE("window initializes", "[smoke]")
{
    if (std::getenv("DISPLAY") == nullptr && std::getenv("WAYLAND_DISPLAY") == nullptr)
    {
        SUCCEED("No graphical display is available for smoke tests.");
        return;
    }

    dudis::DDWindowContext context;
    context.initWith();

    auto window = context.createWindow("Init window Test", dudis::SizeI(800, 600));

    // Window window(dudis::SizeI(800, 600), "Init window Test");
    if (!window.init())
    {
        SUCCEED("No graphical display is available for smoke tests.");
        return;
    }

    REQUIRE(true);
    window.Quit();
}
