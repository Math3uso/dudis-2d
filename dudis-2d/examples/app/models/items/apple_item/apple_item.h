#pragma once

#include "dudis2d/dudis2d.h"

class AppleItem : public dudis::DDModel
{

private:
public:
  AppleItem();
  void start() override;
  void update() override;

  static std::shared_ptr<AppleItem> create() {
    auto model = std::make_shared<AppleItem>();
    return model;
  }
};