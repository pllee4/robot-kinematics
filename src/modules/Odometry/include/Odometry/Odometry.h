/*
 * Odometry.h
 * Created on: Aug 30, 2021 07:14
 * Description:
 * [1]: rotation clockwise means theta negative
 * 
 * Reference:
 * [1] https://www.astro.rug.nl/software/kapteyn-beta/_downloads/attitude.pdf
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
  float w;
  float x;
  float y;
  float z;
} Quaternion;

typedef struct {
  float x;
  float y;
  float theta;
  Quaternion quaternion;
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
