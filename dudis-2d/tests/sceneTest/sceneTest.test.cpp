#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"
#include "dudis2d/debug.h"

using namespace dudis;

TEST_CASE("sceneTest test")
{
    SECTION("It should be able to create a scene")
    {

        test::DDContext::InitContext();

        auto scene = test::MakeScene();

        REQUIRE(scene == true);
    }

    // SECTION("It should be able to execute window with scene")
    // {

    // }
}
