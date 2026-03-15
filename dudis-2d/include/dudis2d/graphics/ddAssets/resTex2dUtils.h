#pragma once

#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/ddAssets/texture2D.h"
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"

// Metodos globais para criação de assets, sem precisar chamar a instancia de scene a todo momento.
namespace dudis
{
    namespace res
    {
        namespace Texture2D
        {
            DDTexture create(const char *path, DDTextureFilter filter = DDTextureFilter::Nearest);
        }
    }
}