cmake_minimum_required(VERSION 3.16)
project(ddtests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

include(FetchContent)

set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_EXTRA_TESTS OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_FUZZERS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)


list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)


add_subdirectory(.. dudis_build)

set(DUDIS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../include")

function(dd_add_test name)
  add_executable(${name} ${name}.test.cpp)

  target_link_libraries(${name} PRIVATE dudis Catch2::Catch2WithMain)

  target_include_directories(${name} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DUDIS_INCLUDE_DIR}
  )

  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${name}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${name}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/${name}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/${name}
  )

  catch_discover_tests(${name})
endfunction()

add_subdirectory(initWindow)
add_subdirectory(sceneTest)