#pragma once

#include "dudis2d/graphics/drawCommand/drawCommand.h"
#include "dudis2d/graphics/blendType.h"

namespace dudis
{

    enum class CommandType
    {
        Draw,
        DrawGroup,
    };

    enum class CommandState
    {
        PushScissor,
        EndScissor,

        PushShader,
        EndShader,

        PushBlendMode,
        EndBlendMode,

        Draw,
    };

    struct DDCommandBuffer
    {
        DrawCommand cmd;
        CommandState state;
    };
};