#pragma once

namespace dudis
{
    /**
     * @brief Define como as cores desenhadas são combinadas com o framebuffer.
     */
    enum class BlendType
    {
        /** @brief Composição alpha padrão (transparência tradicional). */
        AlphaComposite,
        /** @brief Soma a luz/cor da origem ao destino (efeito brilhante). */
        LightAdd,
        /** @brief Multiplica as cores de origem e destino (resultado mais escuro). */
        ColorMultiply,
        /** @brief Soma direta de cores (origem + destino). */
        ColorAdd,
        /** @brief Subtrai a cor da origem do destino. */
        ColorSubtract,
        /** @brief Usa alpha pré-multiplicado para composição correta de sprites preparados. */
        PremultipliedAlpha,
        /** @brief Modo customizado com fatores/equação de blend compartilhados. */
        UserDefined,
        /** @brief Modo customizado com configuração separada para cor e alpha. */
        UserDefinedSeparate,
    };
}
