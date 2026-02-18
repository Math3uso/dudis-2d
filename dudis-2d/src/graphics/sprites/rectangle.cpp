#include "dudis2d/graphics/sprites/rectangle.h"
#include "dudis2d/graphics/drawCommand/drawCommand.h"
#include <iomanip>
using namespace dudis;

dudis::DDRectangle::DDRectangle(SizeF size, Vec2 pos, FillMode fill)
    : Renderable()
{
  this->size = size;
  this->pos = pos;

  this->fill = fill;

  this->type = TypeShape::Rectangle;
  this->setDirty();
}