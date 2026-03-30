#include "support/test_context.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

namespace
{
    double runScenario(const char *label, bool withRectangle, int warmupFrames, int measuredFrames)
    {
        dudis::tests::TestContext context;
        if (!context.init())
        {
            std::cout << label << ": skipped (no graphical display available)\n";
            return 0.0;
        }

        context.pushScene(dudis::tests::makeScene());
        context.windowRef().SetClearColor(dudis::Color::Hex(0x202020FF));

        if (withRectangle)
        {
            context.pushDrawable(dudis::tests::makeQuadDefault());
        }

        context.runFrames(warmupFrames);

        const auto start = std::chrono::steady_clock::now();
        context.runFrames(measuredFrames);
        const auto end = std::chrono::steady_clock::now();

        context.shutdown();

        const auto totalMs = std::chrono::duration<double, std::milli>(end - start).count();
        const auto perFrame = totalMs / measuredFrames;

        std::cout << label << ": " << perFrame << " ms/frame over "
                  << measuredFrames << " frames\n";

        return perFrame;
    }
} // namespace

int main()
{
    const int warmupFrames = 60;
    const int measuredFrames = 240;

    runScenario("empty_scene", false, warmupFrames, measuredFrames);
    runScenario("scene_with_rectangle", true, warmupFrames, measuredFrames);

    return EXIT_SUCCESS;
}
