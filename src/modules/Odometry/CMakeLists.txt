mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

add_executable(OdometryTest src/Odometry.c test/OdometryTest.cpp)

target_include_directories(OdometryTest PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(OdometryTest PRIVATE gtest gmock gtest_main)

gtest_discover_tests(OdometryTest)
add_test(NAME gtest_all COMMAND OdometryTest)


add_library(Odometry STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Odometry.c)
target_include_directories(Odometry PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)