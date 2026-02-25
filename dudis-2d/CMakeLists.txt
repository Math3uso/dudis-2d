

# cmake_minimum_required(VERSION 3.10)
# project(dudis-2d)
# set(CMAKE_CXX_STANDARD 17)

# set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib)
# set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)
# set(RAYGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raygui)

# set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
# set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)

# add_subdirectory(${RAYLIB_DIR})

# file(GLOB_RECURSE SRC_FILES src/*.cpp)

# file(GLOB_RECURSE BOX2D_SRC
#     ${BOX2D_DIR}/src/*.cpp
# )

# add_library(dudis STATIC
#     ${SRC_FILES}
#     ${BOX2D_SRC}
# )

# include(FetchContent)

# FetchContent_Declare(
#   glm
#   GIT_REPOSITORY https://github.com/g-truc/glm.git
#   GIT_TAG 0.9.9.8
# )

# FetchContent_MakeAvailable(glm)

# # Macro pra Debug
# target_compile_definitions(dudis PRIVATE
#     $<$<CONFIG:Debug>:DD_DEBUG>
#     $<$<CONFIG:Release>:DD_RELEASE>
# )

# target_include_directories(dudis PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${RAYGUI_DIR}
#     ${BOX2D_DIR}/include
#     ${RAYLIB_DIR}/src
# )

# target_link_libraries(dudis PUBLIC raylib)


cmake_minimum_required(VERSION 3.16)
project(dudis-2d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib)
set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)
set(RAYGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raygui)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)

# Box2D: disable extras that pull GLFW/testbed to avoid target conflicts
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(${RAYLIB_DIR})
add_subdirectory(${BOX2D_DIR})

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(dudis STATIC ${SRC_FILES})

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(glm)

target_compile_definitions(dudis PRIVATE
    $<$<CONFIG:Debug>:DD_DEBUG>
    $<$<CONFIG:Release>:DD_RELEASE>
)

target_include_directories(dudis PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RAYGUI_DIR}
)

target_link_libraries(dudis
    PUBLIC
        raylib
        box2d
        glm
)
