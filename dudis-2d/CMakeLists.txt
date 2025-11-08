# cmake_minimum_required(VERSION 3.10)
# project(dudis-2d)

# set(CMAKE_CXX_STANDARD 17)

# set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)

# # Encontra todos os .cpp
# file(GLOB_RECURSE SRC_FILES src/*.cpp)

# file(GLOB_RECURSE BOX2D_SRC
#     ${BOX2D_DIR}/src/*.cpp
# )

# # Cria a biblioteca estática
# # add_library(dudis STATIC ${SRC_FILES})

# add_library(dudis STATIC
#     ${SRC_FILES}
#     ${BOX2D_SRC}
# )

# # Inclui os diretórios onde estão os headers
# # Isso permite includes do tipo #include "core/window/window.h"
# target_include_directories(dudis PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/raygui
#     ${BOX2D_DIR}/include
# )

# # Linka com raylib
# find_package(raylib REQUIRED)
# target_link_libraries(dudis PUBLIC raylib)



cmake_minimum_required(VERSION 3.10)
project(dudis-2d)

set(CMAKE_CXX_STANDARD 17)

# Caminho correto do Box2D
set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)

# Pega os .cpp do teu projeto
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Pega os .cpp do Box2D
file(GLOB_RECURSE BOX2D_SRC
    ${BOX2D_DIR}/src/*.cpp
)

# Cria a lib estática com tudo junto
add_library(dudis STATIC
    ${SRC_FILES}
    ${BOX2D_SRC}
)

# Inclui os diretórios de headers
target_include_directories(dudis PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/raygui
    ${BOX2D_DIR}/include
)

# Linka com Raylib
find_package(raylib REQUIRED)
target_link_libraries(dudis PUBLIC raylib)



# v2

# cmake_minimum_required(VERSION 3.10)
# project(dudis-2d)

# set(CMAKE_CXX_STANDARD 17)

# # Caminhos das dependências
# set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib)
# set(BOX2D_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d)
# set(RAYGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/raygui)

# # Configurações do Raylib para build estático
# set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
# set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)

# # Adiciona o Raylib como subdiretório
# add_subdirectory(${RAYLIB_DIR})

# # Pega os .cpp do seu projeto
# file(GLOB_RECURSE SRC_FILES src/*.cpp)

# # Pega os .cpp do Box2D
# file(GLOB_RECURSE BOX2D_SRC
#     ${BOX2D_DIR}/src/*.cpp
# )

# # Cria a biblioteca estática com tudo junto
# add_library(dudis STATIC
#     ${SRC_FILES}
#     ${BOX2D_SRC}
# )

# # Inclui os diretórios de headers
# target_include_directories(dudis PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${RAYGUI_DIR}
#     ${BOX2D_DIR}/include
#     ${RAYLIB_DIR}/src  # Headers do Raylib
# )

# # Linka com Raylib (agora compilado localmente)
# target_link_libraries(dudis PUBLIC raylib)
