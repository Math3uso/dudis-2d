#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"

TEST_CASE("Init window", "[window]")
{
    Window window(dudis::SizeI(800, 600), "Init window Test");
    REQUIRE(window.init() == true);
}
