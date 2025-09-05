#pragma once

#include "dudis2d/dudis2d.h"

class SceneLayout : public Scene {
public:
  void start() override;
  void update() override;

  CREATE_SCENE(SceneLayout);
};