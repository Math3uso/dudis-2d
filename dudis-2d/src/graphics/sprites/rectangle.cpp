#include "dudis2d/graphics/sprites/rectangle.h"
using namespace dudis;

dudis::DDRectangle::DDRectangle(SizeI size, Vec2 pos, FillMode fill)
    : Renderable() {
  this->size = size;
  this->pos = pos;

  this->fill = fill;

  this->type = TypeShape::Rectangle;
}

void dudis::DDRectangle::render() {

  // Rectangle rect = {pos.x, pos.y, (float)size.w, (float)size.h};

  DrawRectanglePro(Rectangle{pos.x, pos.y, (float)size.w, (float)size.h},
                   origin, // origin for rotation
                   angle,  // rotation in radians
                   color   // color of the rectangle
  );
}