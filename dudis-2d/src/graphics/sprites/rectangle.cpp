#include "dudis2d/graphics/sprites/rectangle.h"
#include <iomanip>
using namespace dudis;

dudis::DDRectangle::DDRectangle(SizeI size, Vec2 pos, FillMode fill)
    : Renderable() {
  this->size = size;
  this->pos = pos;

  this->fill = fill;

  this->type = TypeShape::Rectangle;
  this->setDirty();
}

// bool *print = new bool(false);

void dudis::DDRectangle::render() {

  // Entity::render();
  this->getGlobalMatrix();

  // if (!*print) {
  //   auto f = std::cout.flags();
  //   auto prec = std::cout.precision();

  //   for (int row = 0; row < 4; row++) {
  //     std::cout << "| ";
  //     for (int col = 0; col < 4; col++) {
  //       std::cout << std::setw(6) << this->getGlobalMatrix()[col][row] << "
  //       ";
  //     }
  //     std::cout << "|\n";
  //   }

  //   std::cout.flags(f);
  //   std::cout.precision(prec);
  //   *print = true;
  // }

  auto gPos = this->getGlobalPos();
  auto gRotation = this->getGlobalRotation() * RAD2DEG;
  auto gScale = this->getGlocalScale();
  auto finalSize = Size(size.w * gScale.x, size.h * gScale.y);

  Rectangle rect = {gPos.x, gPos.y, (float)finalSize.w, (float)finalSize.h};

  // Rectangle rect = {pos.x, pos.y, (float)size.w, (float)size.h};

  DrawRectanglePro(rect, origin, gRotation, color);

  // DrawRectanglePro(Rectangle{pos.x, pos.y, (float)size.w, (float)size.h},
  //                  origin, // origin for rotation
  //                  angle,  // rotation in radians
  //                  color   // color of the rectangle
  // );
}