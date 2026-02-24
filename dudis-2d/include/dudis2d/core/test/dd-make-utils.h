#pragma once

#include "dudis2d/dudis2d.h"

namespace dudis
{
    namespace test
    {
        class SceneTest : public Scene
        {
        public:
            void update() override {};
            void start() override {};
        };

        inline bool MakeScene()
        {
            auto scene = Scene::create<SceneTest>();

            if (scene)
            {
                return true;
            }

            return false;
        }

        inline std::unique_ptr<SceneTest> MakeSceneWithInstance()
        {
            auto scene = Scene::create<SceneTest>();

            if (scene)
            {
                return scene;
            }

            return nullptr;
        }
    }
}