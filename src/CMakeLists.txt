add_subdirectory(modules)

add_executable(test_draw test_draw.cpp)
target_link_libraries(test_draw PkgConfig::Cairo imcore)

add_subdirectory(ui)
add_executable(test_draw2 test_draw2.cpp)
target_link_libraries(test_draw2 window PkgConfig::Cairo imcore)
