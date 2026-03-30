#include "dudis2d/graphics/ddRenderGroup.h"
#include <algorithm>

using namespace dudis;

RenderQueue *DDRenderGroup::_target = nullptr;
int DDRenderGroup::current = 0;

void DDRenderGroup::initPipeline(RenderQueue *queue)
{
    if (queue)
    {
        // if (current == 0 || queue->getCommands().size() > current)
        // {
        //     current = queue->getCommands().size();
        //     _target = queue;
        //     DDRenderGroup::sortByZ();
        //     // DDRenderGroup::sortByShaders();
        //     // DDRenderGroup::sortByTextures();
        //     // DDRenderGroup::sortByBlendType();
        // }

        current = queue->getCommands().size();
        _target = queue;
        DDRenderGroup::sortByZ();
        // DDRenderGroup::sortByShaders();
        // DDRenderGroup::sortByTextures();
        // DDRenderGroup::sortByBlendType();

        return;
    }
}

void DDRenderGroup::sortByZ()
{
    if (_target == nullptr)
    {
        return;
    }

    auto &commands = _target->getCommands();
    std::stable_sort(commands.begin(), commands.end(),
                     [](const DrawCommand &a, const DrawCommand &b)
                     {
                         return a.z < b.z;
                     });
}
