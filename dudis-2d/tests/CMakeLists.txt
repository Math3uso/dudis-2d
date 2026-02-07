cmake_minimum_required(VERSION 3.10)
project(ddtests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the shared dudis library once for all tests.
add_subdirectory(.. dudis_build)

# Individual test modules (each with its own CMakeLists.txt).
add_subdirectory(unit)
add_subdirectory(initWindow)
