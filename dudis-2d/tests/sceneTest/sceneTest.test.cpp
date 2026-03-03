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

        context.window->SetClearColor(dudis::Color::Default());

        context.window->runByFrames(30);

        context.ExitContext();
    }

    SECTION("It should be able to set scene color using hexadecimal")
    {
        test::DDContext context;
        context.InitContext();

        auto scene = test::MakeSceneWithInstance();

        context.manager->pushScene(std::move(scene));

        context.window->SetClearColor(dudis::Color::Hex(0x202020FF));

        REQUIRE(context.window->getColor() == dudis::Color::Default());

        context.window->runByFrames(1);

        context.ExitContext();
    }

    SECTION("It should be able to draw in scene")
    {
        test::DDContext context;
        context.InitContext();

        auto scene = test::MakeSceneWithInstance();

        context.manager->pushScene(std::move(scene));

        context.window->SetClearColor(dudis::Color::Hex(0x202020FF));

        auto quad = test::MakeQuadDefault();
        context.pushDraw(quad);

        context.window->runByFrames(30);

        context.ExitContext();
    }
}
