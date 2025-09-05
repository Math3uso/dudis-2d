#pragma once

#include "dudis2d/dudis2d.h"

class Player : public dudis::DDModel
{
public:
  Player();
  void start() override;
  void update() override;

  float speed = 1.7f;
  bool isJump = false;

  static std::shared_ptr<Player> create() {
    auto model = std::make_shared<Player>();
    return model;
  }
};