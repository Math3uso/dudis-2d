#pragma once

#include "dudis2d/graphics/color.h"

#include <string>

typedef struct Image Image;

namespace dudis::tests
{
Image captureScreen();
void unloadImage(Image image);
bool exportImageArtifact(Image image, const std::string &name);
dudis::Color samplePixel(const Image &image, int x, int y);
bool colorNear(const dudis::Color &actual, const dudis::Color &expected, int tolerance = 0);
} // namespace dudis::tests
