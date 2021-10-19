/*
 * PotentialField.h
 * Created on: Aug 25, 2021 06:58
 * Description:
 *
 * Reference:
 * https://www.cs.cmu.edu/~motionplanning/lecture/Chap4-Potential-Field_howie.pdf
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#ifndef POTENTIALFIELD_H
#define POTENTIALFIELD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  float speed;
  float theta;
  float distance_goal;
  float angle_goal;
  const float *sensor_distance;
  const float *sensor_direction;
  const float *sensor_threshold;
} PotentialFieldInput;

typedef struct {
  float res_speed;
  float res_theta;
} PotentialFieldOutput;

typedef struct {
  float rep_scaling;
  float att_scaling;
  uint8_t num_sensor;
  float min_detectable_distance;
  float max_turn;
  float max_accel;
  float max_speed;
} PotentialFieldInstance;

typedef struct {
  float x;
  float y;
  float total;
} RepulsivePotentialField;

bool InitPotentialField(PotentialFieldInstance *instance);
PotentialFieldOutput PotentialFieldLoop(PotentialFieldInstance *instance,
                                        PotentialFieldInput input);
// simpler version, just to get Repulsive PotentialField
RepulsivePotentialField GetRepulsivePotentialField(
    PotentialFieldInstance *instance, PotentialFieldInput input);

// input - robot speed, theta, distance goal, angle goal distance from sensor
// output - resultant_speed, theta,

#ifdef __cplusplus
}
#endif

#endif /* POTENTIALFIELD_H */
