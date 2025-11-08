#include "dudis2d/dudis2d.h"

class SceneScn : public Scene {
public:
  void start() override;
  void update() override;
  CREATE_SCENE(SceneScn)
};