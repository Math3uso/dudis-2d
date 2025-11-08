#include "dudis2d/graphics/ui/container/container.h"

using namespace dudis;

void Container::render() {
  DrawRectangleV(pos, {float(size.w), float(size.h)}, backgroundColor);
}

std::shared_ptr<Container> Container::create(Layout nLayout) {
  auto container = std::make_shared<Container>(nLayout);
  return container;
}