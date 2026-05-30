cmake_minimum_required(VERSION 3.16)
project(ddtests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

include(FetchContent)

set(LEGACY_DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/build/_deps")

if(EXISTS "${LEGACY_DEPS_DIR}/catch2-src/CMakeLists.txt")
  set(FETCHCONTENT_SOURCE_DIR_CATCH2 "${LEGACY_DEPS_DIR}/catch2-src")
endif()

if(EXISTS "${LEGACY_DEPS_DIR}/glm-src/CMakeLists.txt")
  set(FETCHCONTENT_SOURCE_DIR_GLM "${LEGACY_DEPS_DIR}/glm-src")
endif()

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

set(TESTS_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(DUDIS_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../include")

option(DD_BUILD_GRAPHICAL_TESTS "Enable platform and smoke tests that require a graphical display" OFF)

add_library(dd_test_support STATIC
  support/test_context.cpp
)

target_link_libraries(dd_test_support PUBLIC dudis)
target_include_directories(dd_test_support
  PUBLIC
    ${TESTS_ROOT_DIR}
    ${DUDIS_INCLUDE_DIR}
)
target_compile_definitions(dd_test_support
  PUBLIC
    DD_TEST_ROOT_DIR="${TESTS_ROOT_DIR}"
    DD_TEST_ASSETS_DIR="${TESTS_ROOT_DIR}/assets"
    DD_TEST_ARTIFACTS_DIR="${CMAKE_BINARY_DIR}/artifacts"
)

function(dd_test_metadata suite out_labels out_timeout out_support_target)
  if(suite STREQUAL "unit")
    set(labels "unit;fast")
    set(timeout 10)
    set(support_target dd_test_support)
  elseif(suite STREQUAL "smoke")
    set(labels "smoke;integration")
    set(timeout 20)
    set(support_target dd_test_support)
  elseif(suite STREQUAL "platform")
    set(labels "platform;integration")
    set(timeout 20)
    set(support_target dd_platform_test_support)
  else()
    message(FATAL_ERROR "Unknown test suite: ${suite}")
  endif()

  set(${out_labels} "${labels}" PARENT_SCOPE)
  set(${out_timeout} "${timeout}" PARENT_SCOPE)
  set(${out_support_target} "${support_target}" PARENT_SCOPE)
endfunction()

function(dd_add_test name)
  cmake_parse_arguments(DD "" "SUITE" "SOURCES;LIBRARIES" ${ARGN})

  if(NOT DD_SUITE)
    message(FATAL_ERROR "dd_add_test requires SUITE")
  endif()

  if(NOT DD_SOURCES)
    message(FATAL_ERROR "dd_add_test requires SOURCES")
  endif()

  if((DD_SUITE STREQUAL "platform" OR DD_SUITE STREQUAL "smoke") AND NOT DD_BUILD_GRAPHICAL_TESTS)
    return()
  endif()

  dd_test_metadata(${DD_SUITE} labels timeout support_target)

  add_executable(${name} ${DD_SOURCES})
  target_link_libraries(${name}
    PRIVATE
      dudis
      Catch2::Catch2WithMain
      ${support_target}
      ${DD_LIBRARIES}
  )
  target_include_directories(${name}
    PRIVATE
      ${TESTS_ROOT_DIR}
      ${DUDIS_INCLUDE_DIR}
  )

  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )

  catch_discover_tests(${name}
    TEST_PREFIX "${DD_SUITE}::"
    WORKING_DIRECTORY "${TESTS_ROOT_DIR}"
    PROPERTIES
      LABELS "${labels}"
      SKIP_REGULAR_EXPRESSION "SKIPPED:"
      SKIP_RETURN_CODE 4
      TIMEOUT ${timeout}
  )
endfunction()

function(dd_add_benchmark name)
  cmake_parse_arguments(DD "" "" "SOURCES;LIBRARIES" ${ARGN})

  if(NOT DD_SOURCES)
    message(FATAL_ERROR "dd_add_benchmark requires SOURCES")
  endif()

  add_executable(${name} ${DD_SOURCES})
  target_link_libraries(${name}
    PRIVATE
      dudis
      dd_test_support
      ${DD_LIBRARIES}
  )
  target_include_directories(${name}
    PRIVATE
      ${TESTS_ROOT_DIR}
      ${DUDIS_INCLUDE_DIR}
  )
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endfunction()

if(DD_BUILD_GRAPHICAL_TESTS)
  add_library(dd_platform_test_support STATIC
    support/platform_test_context.cpp
  )

  target_link_libraries(dd_platform_test_support PUBLIC dudis)
  target_include_directories(dd_platform_test_support
    PUBLIC
      ${TESTS_ROOT_DIR}
      ${DUDIS_INCLUDE_DIR}
  )

  target_compile_definitions(dd_platform_test_support
    PUBLIC
      DD_TEST_ROOT_DIR="${TESTS_ROOT_DIR}"
      DD_TEST_ARTIFACTS_DIR="${CMAKE_BINARY_DIR}/artifacts"
  )
endif()

dd_add_test(entity_unit
  SUITE unit
  SOURCES
    unit/entity/entity.test.cpp
    unit/res/image_data.test.cpp
)

dd_add_test(ddgl_render_gl_platform
  SUITE platform
  SOURCES
    platform/ddgl/render_gl.test.cpp
)

dd_add_test(window_context_platform
  SUITE platform
  SOURCES
    platform/window/window_context.test.cpp
)

# dd_add_test(window_smoke
#   SUITE smoke
#   SOURCES
#     smoke/window/init_window.test.cpp
# )

# dd_add_test(scene_smoke
#   SUITE smoke
#   SOURCES
#     smoke/scene/scene_smoke.test.cpp
# )

# dd_add_benchmark(scene_benchmark
#   SOURCES
#     benchmarks/scene_benchmark.cpp
# )

add_custom_target(dd_benchmarks DEPENDS scene_benchmark)

if(NOT DD_BUILD_GRAPHICAL_TESTS)
  message(STATUS "Graphical platform/smoke tests disabled. Configure with -DDD_BUILD_GRAPHICAL_TESTS=ON to enable them.")
endif()
