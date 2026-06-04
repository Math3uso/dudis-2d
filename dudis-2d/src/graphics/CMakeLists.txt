add_library(dudis-graphics OBJECT
    DDRender/DDRender.cpp
    color.cpp
    # ddAssets/ddTexture.cpp
    # ddAssets/resTex2dUtils.cpp
    # ddAssets/texture2D.cpp
    ddRenderGroup.cpp
    ddgl/render/renderGL.cpp
    frameQueue/frameQueue.cpp
    renderQueue/renderQueue.cpp
    renderable.cpp
    sprites/rectangle.cpp
    sprites/sprite/sprite.cpp
    # utils/animatedList/animatedList.cpp
    # utils/shapeUtils.cpp
    # utils/spriteAnimator/spriteAnimator.cpp
    ddgl/render/renderDevice.cpp
    ddgl/ddglTypes.cpp
    # ${DD_ROOT_DIR}/extern/stb_image.cpp
    res/imageLoader.cpp
)


target_include_directories(dudis-graphics
      PRIVATE
          ${DD_ROOT_DIR}/extern
)


dd_configure_module(dudis-graphics)

target_link_libraries(dudis-graphics
    PRIVATE
        SDL3::SDL3
        glad
)
