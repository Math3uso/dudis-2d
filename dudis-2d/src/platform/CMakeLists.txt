add_library(dudis-platform OBJECT
    ddrlUtils/toRLBlendType.cpp
    ddrlUtils/toRLKey.cpp
    ddrlUtils/toRLMouseButton.cpp
    ddrlUtils/toRLTextureFilter.cpp
    ddrlUtils/toRLTextureFormat.cpp
    ddrlUtils/toRLTextureWrap.cpp
    input/input.cpp
    input/keyboard.cpp
    input/mouse.cpp
    raygui_impl.cpp
    window/window.cpp
    ../globals/app.cpp
)

dd_configure_module(dudis-platform)

target_link_libraries(dudis-platform
    PRIVATE
        raylib
)
