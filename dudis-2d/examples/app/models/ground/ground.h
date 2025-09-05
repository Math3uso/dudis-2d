#pragma once

#include "dudis2d/dudis2d.h"

class Ground : public dudis::DDModel
{

private:
public:
  Ground();
  void start() override;
  void update() override;

  static std::shared_ptr<Ground> create() {
    auto model = std::make_shared<Ground>();
    return model;
  }
};