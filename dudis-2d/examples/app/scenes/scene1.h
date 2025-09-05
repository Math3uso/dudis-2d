#pragma once

#include "dudis2d/dudis2d.h"

class Scene1 : public Scene {
public:
  void start() override;
  void update() override;
  CREATE_SCENE(Scene1);
};