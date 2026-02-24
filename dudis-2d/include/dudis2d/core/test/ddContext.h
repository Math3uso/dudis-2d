#pragma once

#include "dudis2d/dudis2d.h"

namespace dudis
{
    namespace test
    {
        class DDContext
        {
        public:
            DDContext() = default;

            std::unique_ptr<Window> window;
            std::unique_ptr<SceneManager> manager;

            void InitContext();
            void initWindowBySeconds(int seconds);
            void ExitContext();
        };
    }
}
