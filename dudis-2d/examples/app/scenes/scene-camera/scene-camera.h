#pragma once

#include "dudis2d/dudis2d.h"

class SceneCamera : public Scene {
public:
  void start() override;
  void update() override;

  CREATE_SCENE(SceneCamera);
};