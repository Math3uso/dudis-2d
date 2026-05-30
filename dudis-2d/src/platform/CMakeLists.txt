add_library(dudis-platform OBJECT
    ddrlUtils/toRLBlendType.cpp
    ddrlUtils/toRLKey.cpp
    ddrlUtils/toRLMouseButton.cpp
    # ddrlUtils/toRLTextureFilter.cpp
    # ddrlUtils/toRLTextureFormat.cpp
    # ddrlUtils/toRLTextureWrap.cpp
    input/input.cpp
    input/keyboard.cpp
    input/mouse.cpp
    input/backends/raylibInputBackend.cpp
    input/backends/sdlInputBackend.cpp
    raygui_impl.cpp
    window/window.cpp
    ../globals/app.cpp
    platformWindow/RLContext.cpp
    ddWindowContext/ddWindowContext.cpp
     platformWindow/SDLContext.cpp
     platformWindow/platformWindow.cpp

)

dd_configure_module(dudis-platform)

target_link_libraries(dudis-platform
    PRIVATE
        raylib
        SDL3::SDL3
)
