#pragma once

#include "dudis2d/dudis2d.h"

class SceneZOrderBug : public Scene
{
public:
  bool start() override;
  void update() override;
  CREATE_SCENE(SceneZOrderBug);

private:
  std::shared_ptr<dudis::DDRectangle> parentRect;
  std::shared_ptr<dudis::DDRectangle> oldBlueChild;
  std::shared_ptr<dudis::DDRectangle> newRedChild;
  int frameCount = 0;
  bool step2Done = false;
};
