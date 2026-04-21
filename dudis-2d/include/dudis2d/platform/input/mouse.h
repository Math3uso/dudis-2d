#pragma once

#include "dudis2d/platform/input/mouseState.h"
#include "dudis2d/core/math/vec2.h"

namespace dudis
{
    class Mouse
    {
    private:
        static ButtonState _btState[(int)MouseButton::COUNT];
        static void _setMouseButton(MouseButton, bool isDownNow);
        static void _beginFrame();
        static bool _getButtonsStateInRl(MouseButton bt);

    public:
        /**
         * @brief Atualiza o estado do mouse.
         *
         * Deve ser chamado uma vez por frame, antes da leitura do estado do mouse.
         */
        static void update();
        /**
         * @brief Retorna true enquanto o botao estiver pressionado.
         */
        static bool isDown(MouseButton bt) { return _btState[(int)bt].down; };
        /**
         * @brief Retorna true apenas no frame em que o botao foi pressionado.
         */
        static bool isPressed(MouseButton bt) { return _btState[(int)bt].pressed; };
        /**
         * @brief Retorna true apenas no frame em que o botao foi solto.
         */
        static bool isReleased(MouseButton bt) { return _btState[(int)bt].released; };
        /**
         * @brief Alias de isReleased (compatibilidade).
         */
        static bool isUp(MouseButton bt) { return Mouse::isReleased(bt); };
        /**
         * @brief Retorna a posicao atual do cursor em pixels.
         */
        static Vec2 getPosition();
        /**
         * @brief Retorna a posicao atual do cursor em pixels (coordenadas de tela).
         */
        static Vec2 getPositionScreen();
        /**
         * @brief Retorna o delta do mouse desde o ultimo frame.
         */
        static Vec2 getDelta();
        /**
         * @brief Retorna o scroll vertical do mouse no frame atual.
         */
        static float getWheel();
        /**
         * @brief Retorna o scroll horizontal e vertical do mouse no frame atual.
         */
        static Vec2 getWheelDelta();
    };
}
