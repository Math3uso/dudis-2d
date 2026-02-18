add_executable("temp" "temp".test.cpp)

target_link_libraries("temp" PRIVATE dudis)

target_include_directories("temp" PRIVATE
    
    /../../include
)
