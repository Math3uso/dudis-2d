#pragma once

#include <memory>
#include "dudis2d/platform/input/inputBackend.h"

namespace dudis
{

    enum class Axis
    {
        Horizontal,
        Vertical
    };

    enum class InputBackendType
    {
        SDL,
        RL
    };

    class Input
    {
    private:
        static std::unique_ptr<InputBackend> _backend;

    public:
        /**
         * @brief Atualiza o estado de teclado e mouse.
         *
         * Deve ser chamado uma vez por frame no loop da janela.
         */
        static void update();

        static int getAxis(Axis axis);

        static void setBackend(InputBackendType type);

        static InputBackend *getBackend();
    };
}
