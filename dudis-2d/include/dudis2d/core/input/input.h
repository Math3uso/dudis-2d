#pragma once

namespace dudis
{

    enum class Axis
    {
        Horizontal,
        Vertical
    };

    class Input
    {
    public:
        /**
         * @brief Atualiza o estado de teclado e mouse.
         *
         * Deve ser chamado uma vez por frame no loop da janela.
         */
        static void update();

        static int getAxis(Axis axis);
    };
}
