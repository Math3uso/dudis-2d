#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"
#include "dudis2d/debug.h"

using namespace dudis;

TEST_CASE("sceneTest test")
{
    SECTION("It should be able to create a scene")
    {

        test::DDContext context;

        context.InitContext();

        auto scene = test::MakeScene();

        REQUIRE(scene == true);
        context.ExitContext();
    }

    SECTION("It should be able to execute window with scene")
    {
        test::DDContext context;
        context.InitContext();

        auto scene = test::MakeSceneWithInstance();

        context.manager->pushScene(std::move(scene));

        context.window->runByFrames(60);

        context.ExitContext();
    }
}
