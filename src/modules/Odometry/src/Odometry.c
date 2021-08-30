/*
 * Odometry.c
 * Created on: Aug 30, 2021 07:47
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "Odometry/Odometry.h"

#include <math.h>

void InitOdometry(OdometryInstance *instance) { ResetOdometry(instance); }

void ResetOdometry(OdometryInstance *instance) {
  instance->odom.x = 0;
  instance->odom.y = 0;
  instance->odom.theta = 0;
}

Odometry GetOdometry(OdometryInstance *instance) { return instance->odom; }

void OdometryLoop(OdometryInstance *instance, OdometryInput input) {
  float d_x = input.linear_vel * cos(instance->odom.theta) * input.dt;
  float d_y = input.linear_vel * sin(instance->odom.theta) * input.dt;
  float d_theta = input.angular_vel * input.dt;

  instance->odom.x += d_x;
  instance->odom.y += d_y;
  instance->odom.theta += d_theta;
}
