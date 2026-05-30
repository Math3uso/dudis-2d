#include <catch2/catch_test_macros.hpp>
#include "dudis2d/dudis2d.h"
#include "dudis2d/graphics/res/imageLoader.h"
#include "support/test_context.h"

TEST_CASE("load image from file", "[unit]")
{
    auto imageData = dudis::ImageLoader::loadFromFile("assets/player.png");
    REQUIRE(imageData.data != nullptr);

    dudis::ImageLoader::freeImageData(imageData);
    REQUIRE(imageData.data == nullptr);
}

TEST_CASE("load non-existent image", "[unit]")
{
    auto imageData = dudis::ImageLoader::loadFromFile("assets/non_existent.png");
    REQUIRE(imageData.data == nullptr);
}