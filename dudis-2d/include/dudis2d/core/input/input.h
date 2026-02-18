#pragma once

namespace dudis
{
    class Input
    {
    public:
        /**
         * @brief Atualiza o estado de teclado e mouse.
         *
         * Deve ser chamado uma vez por frame no loop da janela.
         */
        static void update();
    };
}
