/*
 * Odometry.h
 * Created on: Aug 30, 2021 07:14
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#ifndef ODOMETRY_H
#define ODOMETRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  float x;
  float y;
  float theta;
} Odometry;

typedef struct {
  float linear_vel;   // m/s
  float angular_vel;  // m/s
  float dt;           // seconds
} OdometryInput;

typedef struct {
  OdometryInput input;
  Odometry odom;
} OdometryInstance;

void InitOdometry(OdometryInstance *instance);
void ResetOdometry(OdometryInstance *instance);
Odometry GetOdometry(OdometryInstance *instance);
void OdometryLoop(OdometryInstance *instance, OdometryInput input);

#ifdef __cplusplus
}
#endif

#endif /* ODOMETRY_H */
