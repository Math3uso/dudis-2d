#pragma once

#include "dudis2d/platform/input/key.h"
#include "dudis2d/platform/input/keyState.h"
#include "dudis2d/platform/input/inputBackend.h"

namespace dudis
{
    class Keyboard
    {

    private:
        static constexpr int _keysCount = (int)KeyCode::COUNT;
        static KeyState _keys[_keysCount];
        static void _beginFrames();
        static void _setKeyDown(KeyCode key, bool isDownNow);

    public:
        /**
         * @brief Atualiza o estado do teclado.
         *
         * Deve ser chamado uma vez por frame, antes da leitura do estado das teclas.
         */
        static void update(InputBackend *backend);
        /**
         * @brief Retorna true enquanto a tecla estiver pressionada.
         */
        static bool isDown(KeyCode key) { return _keys[(int)key].down; };
        /**
         * @brief Retorna true apenas no frame em que a tecla foi pressionada.
         */
        static bool isPressed(KeyCode key) { return _keys[(int)key].pressed; };
        /**
         * @brief Retorna true apenas no frame em que a tecla foi solta.
         */
        static bool isReleased(KeyCode key) { return _keys[(int)key].released; };
        /**
         * @brief Alias de isReleased (compatibilidade).
         */
        static bool isUp(KeyCode key) { return Keyboard::isReleased(key); };
    };
}
