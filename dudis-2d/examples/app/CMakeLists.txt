cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

# Adiciona o diretório da biblioteca dudis2d
add_subdirectory(../../ ../../build)

# Encontra todos os arquivos .cpp automaticamente (excluindo arquivos do CMake)
file(GLOB_RECURSE APP_SOURCES 
    "*.cpp"
)

# Filtra arquivos do CMake
list(FILTER APP_SOURCES EXCLUDE REGEX ".*CMake.*")
list(FILTER APP_SOURCES EXCLUDE REGEX ".*CompilerId.*")

# Encontra todos os arquivos .h para monitoramento
file(GLOB_RECURSE APP_HEADERS 
    "*.h"
    "*.hpp"
)

# Cria o executável do jogo
add_executable(app ${APP_SOURCES})

# Linka com a biblioteca dudis2d e raylib
target_link_libraries(app dudis raylib)

# Inclui os diretórios de headers
target_include_directories(app PRIVATE
    ../../include
    ../../extern/raygui
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Configura para reconhecer novos arquivos automaticamente
set_property(TARGET app PROPERTY CXX_STANDARD 17)
set_property(TARGET app PROPERTY CXX_STANDARD_REQUIRED ON)

# Adiciona os headers como dependências para forçar recompilação quando mudarem
set_target_properties(app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Configura para monitorar mudanças nos arquivos
if(APP_HEADERS)
    set_source_files_properties(${APP_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)
endif()
