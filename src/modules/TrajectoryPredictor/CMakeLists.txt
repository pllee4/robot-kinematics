mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

add_executable(TrajectoryPredictorTest src/TrajectoryPredictor.c test/TrajectoryPredictorTest.cpp)

target_include_directories(TrajectoryPredictorTest PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(TrajectoryPredictorTest PRIVATE gtest gmock gtest_main)

gtest_discover_tests(TrajectoryPredictorTest XML_OUTPUT_DIR ${PROJECT_BINARY_DIR}/test-reports)
add_test(NAME gtest_all COMMAND TrajectoryPredictorTest)

add_library(TrajectoryPredictor STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TrajectoryPredictor.c)
target_include_directories(TrajectoryPredictor PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
