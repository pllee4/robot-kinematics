add_subdirectory(modules)

add_executable(test_draw test_draw.cpp)
target_link_libraries(test_draw PkgConfig::Cairo imcore)
