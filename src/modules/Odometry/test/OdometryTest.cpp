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
  EXPECT_EQ(odometry_instance.odom.quaternion.w, 0.0);
  EXPECT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_EQ(odometry_instance.odom.quaternion.z, 0.0);
}

TEST(Odometry, ResetOdometry) {
  odometry_instance.odom.x = 1.0;
  odometry_instance.odom.y = 2.0;
  odometry_instance.odom.theta = 3.0;

  odometry_instance.odom.quaternion.w = 0.1;
  odometry_instance.odom.quaternion.x = 0.2;
  odometry_instance.odom.quaternion.y = 0.3;
  odometry_instance.odom.quaternion.z = 0.4;

  ResetOdometry(&odometry_instance);

  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.w, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.z, 0.0);
}

TEST(Odometry, GetOdometry) {
  odometry_instance.odom.x = 1.0;
  odometry_instance.odom.y = 2.0;
  odometry_instance.odom.theta = 3.0;

  odometry_instance.odom.quaternion.w = 0.1;
  odometry_instance.odom.quaternion.x = 0.2;
  odometry_instance.odom.quaternion.y = 0.3;
  odometry_instance.odom.quaternion.z = 0.4;

  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).x, 1.0);
  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).y, 2.0);
  EXPECT_FLOAT_EQ(GetOdometry(&odometry_instance).theta, 3.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.w, 0.1);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.2);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.3);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.z, 0.4);
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
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.w, 1.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.z, 0.0);

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 2.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.w, 1.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.z, 0.0);

  odometry_input.linear_vel = 1.0;
  odometry_input.angular_vel = 1.0;
  odometry_input.dt = 1.0;

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 3.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 1.0);
  EXPECT_NEAR(odometry_instance.odom.quaternion.w, 0.877583, 1.0e-6);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_NEAR(odometry_instance.odom.quaternion.z, 0.479426, 1.0e-6);

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 3.0 + cos(1.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0 + sin(1.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, 2.0);

  EXPECT_NEAR(odometry_instance.odom.quaternion.w, 0.540302, 1.0e-6);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_NEAR(odometry_instance.odom.quaternion.z, 0.841471, 1.0e-6);

  odometry_input.linear_vel = -1.0;
  odometry_input.angular_vel = -3.0;
  odometry_input.dt = 1.0;

  OdometryLoop(&odometry_instance, odometry_input);
  EXPECT_FLOAT_EQ(odometry_instance.odom.x, 3.0 + cos(1.0) - cos(2.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.y, 0.0 + sin(1.0) - sin(2.0));
  EXPECT_FLOAT_EQ(odometry_instance.odom.theta, -1.0);

  EXPECT_NEAR(odometry_instance.odom.quaternion.w, 0.877583, 1.0e-6);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.x, 0.0);
  EXPECT_FLOAT_EQ(odometry_instance.odom.quaternion.y, 0.0);
  EXPECT_NEAR(odometry_instance.odom.quaternion.z, -0.479426, 1.0e-6);
}