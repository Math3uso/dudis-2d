#include "support/visual_check.h"

#include "support/test_paths.h"

#include "raylib.h"

#include <filesystem>

namespace dudis::tests
{
    Image captureScreen()
    {
        return LoadImageFromScreen();
    }

    void unloadImage(Image image)
    {
        UnloadImage(image);
    }

    bool exportImageArtifact(Image image, const std::string &name)
    {
        std::filesystem::create_directories(artifactsDir());
        return ExportImage(image, artifactPath(name).string().c_str());
    }

    dudis::Color samplePixel(const Image &image, int x, int y)
    {
        const ::Color pixel = GetImageColor(image, x, y);
        return dudis::Color(pixel.r, pixel.g, pixel.b, pixel.a);
    }

    bool colorNear(const dudis::Color &actual, const dudis::Color &expected, int tolerance)
    {
        return std::abs(static_cast<int>(actual.r) - static_cast<int>(expected.r)) <= tolerance &&
               std::abs(static_cast<int>(actual.g) - static_cast<int>(expected.g)) <= tolerance &&
               std::abs(static_cast<int>(actual.b) - static_cast<int>(expected.b)) <= tolerance &&
               std::abs(static_cast<int>(actual.a) - static_cast<int>(expected.a)) <= tolerance;
    }
} // namespace dudis::tests
