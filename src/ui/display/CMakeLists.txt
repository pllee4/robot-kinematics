add_library(display STATIC src/display_base.cpp)
target_link_libraries(display PUBLIC window)
target_include_directories(display PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)