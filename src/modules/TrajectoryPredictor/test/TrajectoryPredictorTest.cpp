/* 
 * TrajectoryPredictorTest.cpp
 * Created on: Oct 30, 2021 21:17
 * Description: 
 * 
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 

#include "gtest/gtest.h"

#include "TrajectoryPredictor/TrajectoryPredictor.h"

TEST(TrajectoryPredictor, GetTrajectoryPoints) {
  TrajectoryConfig trajectory_config;
  trajectory_config.sampling_time = 1;
  trajectory_config.linear = 0.1;
  trajectory_config.angular = 0.1;
  trajectory_config.type = RungeKutta;
  trajectory_config.initial_points = {0.0, 0.0};
  EXPECT_FLOAT_EQ(GetFinalPointDistance(trajectory_config), 0.1);
}