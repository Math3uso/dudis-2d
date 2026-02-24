#pragma once

#include "dudis2d/dudis2d.h"

namespace dudis
{
    namespace test
    {
        class DDContext
        {
        public:
            static Window window;
            static SceneManager manager;

            static void InitContext();
            static void initWindowBySeconds(int seconds);
            static void exitContext();
        };
    }
}