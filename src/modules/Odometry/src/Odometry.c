/*
 * Odometry.c
 * Created on: Aug 30, 2021 07:47
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "Odometry/Odometry.h"

#include <math.h>

/*
 * Rotation Matrix
 * 
 * Rz (theta) = | cos(theta)  sin(theta)  0  |      
 *              | -sin(theta) cos(theta)  0  |
 *              |  0            0         1  |
 */

// private struct
typedef struct {
  float r[3][3];
} RotationMatrix;

// private function
Quaternion CreateQuaternionFromYaw(float theta) {
  RotationMatrix matrix;
  matrix.r[0][0] = cos(theta);
  matrix.r[0][1] = sin(theta);
  matrix.r[0][2] = 0;

  matrix.r[1][0] = -sin(theta);
  matrix.r[1][1] = cos(theta);
  matrix.r[1][2] = 0;

  matrix.r[2][0] = 0;
  matrix.r[2][1] = 0;
  matrix.r[2][2] = 1;

  Quaternion q;
  q.w = sqrt(1 + matrix.r[0][0] + matrix.r[1][1] + matrix.r[2][2]) / 2;
  q.x = (matrix.r[1][2] - matrix.r[2][1]) / (4 * q.w);
  q.y = (matrix.r[2][0] - matrix.r[0][2]) / (4 * q.w);
  q.z = (matrix.r[0][1] - matrix.r[1][0]) / (4 * q.w);
  return q;
}

// public function
void InitOdometry(OdometryInstance *instance) { ResetOdometry(instance); }

void ResetOdometry(OdometryInstance *instance) {
  instance->odom.x = 0;
  instance->odom.y = 0;
  instance->odom.theta = 0;
  instance->odom.quaternion.w = 0;
  instance->odom.quaternion.x = 0;
  instance->odom.quaternion.y = 0;
  instance->odom.quaternion.z = 0;
}

Odometry GetOdometry(OdometryInstance *instance) { return instance->odom; }

void OdometryLoop(OdometryInstance *instance, OdometryInput input) {
  float d_x = input.linear_vel * cos(instance->odom.theta) * input.dt;
  float d_y = input.linear_vel * sin(instance->odom.theta) * input.dt;
  float d_theta = input.angular_vel * input.dt;

  instance->odom.x += d_x;
  instance->odom.y += d_y;
  instance->odom.theta += d_theta;

  instance->odom.quaternion = CreateQuaternionFromYaw(instance->odom.theta);
}
