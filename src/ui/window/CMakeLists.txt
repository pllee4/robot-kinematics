add_library(window STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/window_impl.cpp)
target_link_libraries(window PUBLIC PkgConfig::Cairo imcore)
target_include_directories(window PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
