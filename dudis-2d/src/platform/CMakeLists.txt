add_library(dudis-platform OBJECT
    input/input.cpp
    input/keyboard.cpp
    input/mouse.cpp
    input/backends/sdlInputBackend.cpp
    window/window.cpp
    ../globals/app.cpp
    ddWindowContext/ddWindowContext.cpp
     platformWindow/SDLContext.cpp
     platformWindow/platformWindow.cpp

)

dd_configure_module(dudis-platform)

target_link_libraries(dudis-platform
    PRIVATE
        SDL3::SDL3
)
