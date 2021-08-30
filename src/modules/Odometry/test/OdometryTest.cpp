/*
 * OdometryTest.cpp
 * Created on: Aug 30, 2021 21:27
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "gtest/gtest.h"

#include <math.h>
#include "Odometry/Odometry.h"

OdometryInstance odometry_instance;

TEST(Odometry, Initialization) {
  InitOdometry(&odometry_instance);
  EXPECT_EQ(odometry_instance.odom.x, 0.0);
  EXPECT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_EQ(odometry_instance.odom.theta, 0.0);
}

TEST(Odometry, ResetOdometry) {
  odometry_instance.odom.x = 1.0;
  odometry_instance.odom.y = 2.0;
  odometry_instance.odom.theta = 3.0;
  ResetOdometry(&odometry_instance);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 0.0);
}

TEST(Odometry, GetOdometry) {
  odometry_instance.odom.x = 1.0;
  odometry_instance.odom.y = 2.0;
  odometry_instance.odom.theta = 3.0;
  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).x, 1.0);
  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).y, 2.0);
  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).theta, 3.0);
}

TEST(Odometry, OdometryLoop) {
  ResetOdometry(&odometry_instance);
  OdometryInput odometry_input;
  odometry_input.linear_vel = 1.0;
  odometry_input.angular_vel = 0.0;
  odometry_input.dt = 1.0;

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 1.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 0.0);

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 2.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 0.0);

  odometry_input.linear_vel = 1.0;
  odometry_input.angular_vel = 1.0;
  odometry_input.dt = 1.0;

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 3.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 1.0);

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 3.0 + cos(1.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0 + sin(1.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 2.0);
}