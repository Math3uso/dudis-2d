add_executable(initWindow initWindow.test.cpp)

target_link_libraries(initWindow PRIVATE dudis)

target_include_directories(initWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
