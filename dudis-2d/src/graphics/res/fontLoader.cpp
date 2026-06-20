#include <fstream>
#include <vector>

#define STB_TRUETYPE_IMPLEMENTATION
#include "dudis2d/graphics/res/fontLoader.h"

using namespace std;
using namespace dudis;

FontLoader::FontData FontLoader::loadTTF(const char *path)
{
    vector<unsigned char> ttfBuffer;

    FontData data;

    int fontAtlasW = 512;
    int fontAtlasH = 512;

    // abre indo pro final
    std::ifstream f(path, std::ios::binary | std::ios::ate);

    if (f.is_open())
    {
        std::streamsize size = f.tellg(); // pega o tamanho do arquivo
        f.seekg(0, std::ios::beg);        // volta pro inicio
        ttfBuffer.resize(size);
        f.read(reinterpret_cast<char *>(ttfBuffer.data()), size);
        f.close();
    }

    stbtt_fontinfo font;

    int offset = stbtt_GetFontOffsetForIndex(ttfBuffer.data(), 0);
    if (offset < 0 || !stbtt_InitFont(&font, ttfBuffer.data(), offset))
    {
        return data; // Arquivo corrompido ou formato incompatível
    }

    // stbtt_InitFont(&font, ttfBuffer.data(), stbtt_GetFontOffsetForIndex(ttfBuffer.data(), 0));

    // Isso é um array de pixels (imagem) em memória.
    // cada pixel indo de 0 - 255 (grayScale)
    std::vector<unsigned char> bitmap(fontAtlasW * fontAtlasH, 0);
    data.bitmaps.resize(96 - 32);
    // unsigned char bitmap[fontAtlasW * fontAtlasH];

    stbtt_BakeFontBitmap(
        ttfBuffer.data(), offset,
        32.f,
        bitmap.data(), fontAtlasW, fontAtlasH,
        32, 96,
        data.cdata.data()
        //
    );

    // data.bitmaps.assign(bitmap, bitmap + sizeof(bitmap));
    data.bitmaps = std::move(bitmap);
    data.bitmapW = fontAtlasW;
    data.bitmapH = fontAtlasH;
    data.pixelH = 32;

    return data;
}

// std::vector<unsigned char> createTTFBuffer(const char *path)
// {
// }

vector<unsigned char> FontLoader::createTTFBuffer(const char *path)
{

    vector<unsigned char> ttfBuffer;
    int fontAtlasW = 512;
    int fontAtlasH = 512;

    std::ifstream f(path, std::ios::binary | std::ios::ate);

    if (!f.is_open())
    {
        puts("[ERRO] invalide path");
        return FontLoader::DD_INVALIDE_TTF_BUFFER;
    }
    std::streamsize size = f.tellg();
    f.seekg(0, std::ios::beg);
    ttfBuffer.resize(size);
    f.read(reinterpret_cast<char *>(ttfBuffer.data()), size);
    f.close();

    return ttfBuffer;
};

FontLoader::FontData FontLoader::createFontWithTTFBuffer(std::vector<unsigned char> &buffer, float size)
{
    stbtt_fontinfo font;
    FontData data;

    int fontAtlasW = 512;
    int fontAtlasH = 512;

    int offset = stbtt_GetFontOffsetForIndex(buffer.data(), 0);
    if (offset < 0 || !stbtt_InitFont(&font, buffer.data(), offset))
    {
        puts("[ERROR] Arquivo corrompido ou formato incompatível");
        return data;
    }

    std::vector<unsigned char> bitmap(fontAtlasW * fontAtlasH, 0);
    data.bitmaps.resize(96 - 32);

    stbtt_BakeFontBitmap(
        buffer.data(), offset,
        size,
        bitmap.data(), fontAtlasW, fontAtlasH,
        32, 96,
        data.cdata.data()
        //
    );

    data.bitmaps = std::move(bitmap);
    data.bitmapW = fontAtlasW;
    data.bitmapH = fontAtlasH;
    data.pixelH = size;

    return data;
}