add_executable(test_plot test_plot.cpp)
target_link_libraries(test_plot TrajectoryPredictor window PkgConfig::Cairo imcore)