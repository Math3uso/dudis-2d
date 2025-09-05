#pragma once

#include "dudis2d/graphics/utils/spriteAnimator/spriteAnimator.h"
#include <string>
#include <unordered_map>

class Scene;

namespace dudis {
class AnimatedList
{
protected:
  std::unordered_map<std::string, std::shared_ptr<SpriteAnimator>> animations;
  std::string current;
  Scene *scene = nullptr;

public:
  AnimatedList() {};
  void addToList(const std::string &name,
                 std::shared_ptr<SpriteAnimator> animation);
  void start(const std::string &name);
  std::vector<std::shared_ptr<SpriteAnimator>> Animations();
  void drawToScene(Scene *scene);

  std::shared_ptr<SpriteAnimator> getCurrentAnimation() {
    return animations[current];
  }

  void stop(const std::string &name);

  static std::shared_ptr<AnimatedList> create() {
    auto list = std::make_shared<AnimatedList>();
    return list;
  };
};
} // namespace dudis