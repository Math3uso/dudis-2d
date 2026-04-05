#pragma once

namespace dudis
{
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
}