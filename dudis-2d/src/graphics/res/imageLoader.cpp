#include <iostream>
#include "dudis2d/graphics/res/imageLoader.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace dudis;

ImageData ImageLoader::loadFromFile(const char *path, bool flipVertically)
{
    ImageData imageData{};

    stbi_set_flip_vertically_on_load(flipVertically);

    int width, height, channels;
    uint8_t *data = stbi_load(path, &width, &height, &channels, 0);
    if (data)
    {
        imageData.width = width;
        imageData.height = height;
        imageData.channels = channels;
        imageData.data = data;
    }
    else
    {
        //     // Lidar com erro de carregamento
        std::cerr << "Failed to load image: " << path << std::endl;
        return INVALID_IMAGE_DATA;
    }

    return imageData;
}

void ImageLoader::freeImageData(ImageData &imageData)
{
    if (imageData.data)
    {
        stbi_image_free(imageData.data);
        imageData = INVALID_IMAGE_DATA;
    }
}