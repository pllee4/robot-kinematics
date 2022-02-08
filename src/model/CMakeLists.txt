add_library(model STATIC 
    src/ackermann/ackermann.cpp 
    src/ackermann/ackermann_impl.cpp)
target_link_libraries(model PUBLIC imcore PkgConfig::Cairo display)
target_include_directories(model PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)