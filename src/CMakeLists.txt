add_subdirectory(modules)

add_subdirectory(ui)
add_executable(test_draw test_draw.cpp)
target_link_libraries(test_draw window PkgConfig::Cairo imcore)
