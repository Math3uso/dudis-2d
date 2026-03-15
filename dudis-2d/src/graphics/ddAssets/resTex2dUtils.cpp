#include "dudis2d/graphics/ddAssets/resTex2dUtils.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"
#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"

namespace dudis
{
    namespace res
    {
        namespace Texture2D
        {
            DDTexture create(const char *path, DDTextureFilter filter)
            {
                auto scene = App::getSceneManager().getCurrentScene();
                auto &texManager = scene->getTexture2DManager();

                if (!scene)
                {
                    return DDTexture();
                }

                return texManager.create(path, filter);
            }
        }
    }
}