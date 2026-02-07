add_executable(unit unit.test.cpp)

target_link_libraries(unit PRIVATE dudis)

target_include_directories(unit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
