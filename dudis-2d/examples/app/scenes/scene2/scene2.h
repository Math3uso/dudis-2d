#pragma once

#include "dudis2d/dudis2d.h"
#include "dudis2d/graphics.h"

class Scene2 : public Scene {
public:
  dudis::DDRectangle *sprite;
  void start() override;
  void update() override;
  CREATE_SCENE(Scene2);
};