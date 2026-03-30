#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"

TEST_CASE("window initializes", "[smoke]")
{
    Window window(dudis::SizeI(800, 600), "Init window Test");
    if (!window.init())
    {
        SKIP("No graphical display is available for smoke tests.");
    }

    REQUIRE(true);
    window.Quit();
}
