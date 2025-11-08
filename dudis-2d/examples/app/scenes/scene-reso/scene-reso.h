#pragma once

#include "dudis2d/dudis2d.h"

class SceneReso : public Scene {
public:
  void start() override;
  void update() override;
  CREATE_SCENE(SceneReso);
};