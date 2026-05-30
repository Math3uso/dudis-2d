cmake_minimum_required(VERSION 3.16)
project(dudis-2d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib)
set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)
# set(RAYGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raygui)
set(SDL3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL)
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)

# Box2D: disable extras that pull GLFW/testbed to avoid target conflicts
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)

# --- CONFIGURAÇÃO DO RAYLIB PARA ANDROID ---
if(ANDROID)
    set(PLATFORM "Android" CACHE STRING "" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
else()
    set(PLATFORM "Desktop" CACHE STRING "" FORCE)
endif()



add_subdirectory(${RAYLIB_DIR})
add_subdirectory(${BOX2D_DIR})
add_subdirectory(${SDL3_DIR})

option(DD_SHARED "Construir como biblioteca dinâmica (.dll/.so)" OFF)
# temp
option(ANDROID "Compilar para Android" OFF)

include(FetchContent)

find_path(DD_SYSTEM_GLM_INCLUDE_DIR
    NAMES glm/glm.hpp
)

if(DD_SYSTEM_GLM_INCLUDE_DIR)
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE ${DD_SYSTEM_GLM_INCLUDE_DIR})
else()
    FetchContent_Declare(
      glm
      GIT_REPOSITORY https://github.com/g-truc/glm.git
      GIT_TAG 0.9.9.8
    )

    FetchContent_MakeAvailable(glm)
endif()

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE ${RAYLIB_DIR}/src)


set(DD_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

function(dd_configure_module target)
    target_include_directories(${target}
        PUBLIC
            ${DD_ROOT_DIR}/include
    )
    target_compile_definitions(${target}
        PRIVATE
            $<$<CONFIG:Debug>:DD_DEBUG>
            $<$<CONFIG:Release>:DD_RELEASE>
    )
endfunction()

add_subdirectory(src/core)
add_subdirectory(src/graphics)
add_subdirectory(src/scenes)
add_subdirectory(src/platform)

if(ANDROID OR DD_SHARED)
    add_library(dudis SHARED src/android_stub.cpp)
else()
    add_library(dudis STATIC src/android_stub.cpp)
endif()

if(DD_SHARED)
    target_compile_definitions(dudis PRIVATE DD_BUILD_SHARED)
endif()

dd_configure_module(dudis)

target_sources(dudis
    PRIVATE
        $<TARGET_OBJECTS:dudis-core>
        $<TARGET_OBJECTS:dudis-graphics>
        $<TARGET_OBJECTS:dudis-scenes>
        $<TARGET_OBJECTS:dudis-platform>
)

if(ANDROID)
    target_link_libraries(dudis PUBLIC android)
endif()

target_link_libraries(dudis
    PUBLIC
        dudis-core
        dudis-graphics
        dudis-scenes
        dudis-platform
        glad
    PRIVATE
        raylib
        box2d
        glm
        SDL3::SDL3
)
