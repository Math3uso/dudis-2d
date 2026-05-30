#pragma once

#include <cstdint>

/// @file imageLoader.h
/// @brief Declaração da estrutura ImageData e da função de carregamento de imagens.
// n fica em ddgl pq pode ser usada em outras partes do código, como na criação de texturas
namespace dudis
{
    struct ImageData
    {
        uint32_t width;
        uint32_t height;
        uint32_t channels;
        uint8_t *data;

        bool operator==(const ImageData &other) const
        {
            return width == other.width &&
                   height == other.height &&
                   channels == other.channels &&
                   data == other.data;
        }
    };

    constexpr ImageData INVALID_IMAGE_DATA = ImageData{0, 0, 0, nullptr};
    constexpr uint32_t DD_INVALID_IMAGE_ID = 0;

    namespace ImageLoader
    {
        /// @brief Carrega uma imagem de um arquivo na memória.
        /// @param path O caminho para o arquivo de imagem.
        /// @param flipVertically Indica se a imagem deve ser invertida verticalmente ao carregar (útil para coordenadas de textura).
        /// @return Uma estrutura ImageData contendo os dados da imagem ou INVALID_IMAGE_DATA em caso de falha.
        ImageData loadFromFile(const char *path, bool flipVertically = false);

        /// @brief Libera a memória alocada para os dados da imagem.
        /// @param imageData A estrutura ImageData cujos dados devem ser liberados. Após a liberação, imageData será definido como INVALID_IMAGE_DATA.
        void freeImageData(ImageData &imageData);
    }
}