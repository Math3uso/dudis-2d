#include "dudis2d/graphics/utils/animatedList/animatedList.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/scenes/scene/scene.h"

using namespace std;
using namespace dudis;

void AnimatedList::addToList(const string &name,
                             shared_ptr<SpriteAnimator> animation) {
  if (animations.find(name) != animations.end()) {
    Log::Error("chave ja existente");
    return;
  }

  current = name;
  animations[name] = animation;
  animations[current]->setOpacity(0);
  animations[current]->setLoop(false);
  return;
}

void AnimatedList::start(const string &name) {

  if (animations.find(name) == animations.end())
    return;

  if (animations.find(current) != animations.end()) {
    animations[current]->setOpacity(0);
    animations[current]->setLoop(false);
  }

  current = name;
  animations[current]->setOpacity(1);
  animations[current]->setLoop(true);
  // animations[current]->reset();

  // if (animations.find(name) != animations.end()) {

  //   animations[current]->reset();
  //   animations[current]->setLoop(false);

  //   animations[name]->setLoop(true);
  //   current = name;

  //   if (scene) {
  //     puts("desenhando na scene");
  //     this->drawToScene(scene);
  //   }

  //   return;
  // }
  // return;
}

vector<shared_ptr<SpriteAnimator>> AnimatedList::Animations() {

  vector<shared_ptr<SpriteAnimator>> list;

  for (const auto &animated : animations) {
    list.push_back(animated.second);
  }

  return list;
}

void AnimatedList::drawToScene(Scene *scene) {

  if (this->scene)
    return;

  this->scene = scene;

  for (const auto &animated : animations) {
    animated.second->setOpacity(0.f);
    this->scene->addToRender(animated.second);
  }

  // for (const auto &animated : animations) {

  //   if (animated.first == current) {
  //     // cout << "animation atual -> " << current << "\n";
  //     if (!this->scene) {
  //       this->scene = scene;
  //       this->scene->addToRender(animated.second);
  //       continue;
  //     }
  //     puts("desenhando direto");
  //     cout << "scene -> " << this->scene->label << "\n";
  //     this->scene->addToRender(animated.second);

  //     Log::Alert("fim de drawToScene");
  //     continue;
  //   }
  // }
}

void AnimatedList::stop(const string &name) {
  if (this->animations[name]) {
    animations[name]->setOpacity(0);
    animations[name]->setLoop(false);
    cout << "parando\n";
  }
}