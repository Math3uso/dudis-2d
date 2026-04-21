#pragma once

#include "dudis2d/dudis2d.h"

class SceneBloco : public Scene
{
public:
    bool start() override;
    void update() override;
    int pos = 0;
};
