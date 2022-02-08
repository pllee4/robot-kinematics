add_library(ackermann STATIC src/ackermann/ackermann.cpp src/ackermann/ackermann_impl.cpp)
target_link_libraries(ackermann PUBLIC imcore PkgConfig::Cairo display)
target_include_directories(ackermann PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)