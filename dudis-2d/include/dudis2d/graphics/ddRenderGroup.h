#pragma once

#include "dudis2d/graphics/renderQueue/renderQueue.h"

class Scene;

namespace dudis
{

    class DDRenderGroup
    {
    private:
        static RenderQueue *_target;
        static int current;

    public:
        static void initPipeline(RenderQueue *queue);
        static void sortByZ();
        static void sortByTextures();
        static void sortByShaders();
        static void sortByBlendType();
    };
}
