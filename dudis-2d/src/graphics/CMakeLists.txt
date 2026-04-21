add_library(dudis-graphics OBJECT
    DDRender/DDRender.cpp
    color.cpp
    ddAssets/ddTexture.cpp
    ddAssets/resTex2dUtils.cpp
    ddAssets/texture2D.cpp
    ddRenderGroup.cpp
    ddrlUtils/ddrlUtils.cpp
    frameQueue/frameQueue.cpp
    renderQueue/renderQueue.cpp
    renderable.cpp
    sprites/rectangle.cpp
    sprites/sprite/sprite.cpp
    utils/animatedList/animatedList.cpp
    utils/shapeUtils.cpp
    utils/spriteAnimator/spriteAnimator.cpp
)

dd_configure_module(dudis-graphics)

target_link_libraries(dudis-graphics
    PRIVATE
        raylib
)
