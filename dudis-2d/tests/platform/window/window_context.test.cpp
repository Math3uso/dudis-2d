#include <catch2/catch_test_macros.hpp>

#include "support/platform_test_context.h"

TEST_CASE("window platform context initializes and shuts down", "[platform][window]")
{
    dudis::tests::PlatformTestContext context;
    if (!context.initOpenGLWindow("Window platform test", dudis::SizeI(320, 240)))
    {
        SUCCEED("No graphical display is available for platform window tests.");
        return;
    }

    REQUIRE(context.platformWindowRef()->getSize().w == 320);
    REQUIRE(context.platformWindowRef()->getSize().h == 240);

    context.shutdown();
}
