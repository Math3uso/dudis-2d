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

    stbtt_InitFont(&font, ttfBuffer.data(), stbtt_GetFontOffsetForIndex(ttfBuffer.data(), 0));

    // Isso é um array de pixels (imagem) em memória.
    // cada pixel indo de 0 - 255 (grayScale)
    unsigned char bitmap[512 * 512];

    stbtt_BakeFontBitmap(
        ttfBuffer.data(), 0,
        32.f,
        bitmap, 512, 512,
        32, 96,
        data.cdata.data()
        //
    );

    data.bitmaps.assign(bitmap, bitmap + sizeof(bitmap));

    return data;
}
