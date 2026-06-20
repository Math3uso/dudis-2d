#include <catch2/catch_test_macros.hpp>

#include "dudis2d/core/math/rect.h"

using namespace dudis;

TEST_CASE("rect can be constructed at runtime", "[unit][math]")
{
    float x = 1.0f;
    float y = 2.0f;
    float w = 3.0f;
    float h = 4.0f;

    DDRect direct{x, y, w, h};
    DDRect copy = DDRect(x, y, w, h);

    REQUIRE(direct == DDRect{1.0f, 2.0f, 3.0f, 4.0f});
    REQUIRE(copy == direct);
}

TEST_CASE("rect can be constructed as const and constexpr", "[unit][math]")
{
    const DDRect constRect{0.0f, 0.0f, 0.0f, 0.0f};
    constexpr DDRect constexprRect{5.0f, 6.0f, 7.0f, 8.0f};

    static_assert(constexprRect == DDRect{5.0f, 6.0f, 7.0f, 8.0f});

    REQUIRE(constRect == DDRECT_NONE);
    REQUIRE(constexprRect != constRect);
}
