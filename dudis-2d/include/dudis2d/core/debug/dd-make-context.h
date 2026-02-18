#pragma once

#include <memory.h>
#include "dudis2d/dudis2d.h"

namespace dudis
{
    namespace debug
    {
        inline void DDMakeContext(std::unique_ptr<Scene> scene)
        {
            Window window(SizeI(800, 600), "Janela");
            window.init();
            window.keepWindowCentered(true);

            SceneManager manager;
            manager.pushScene(std::move(scene));

            App::setSceneManager(manager);
            window.SetRenderManager(manager);

            window.Running();
            puts("[INFO] exit test context");
        }
    }
}