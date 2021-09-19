/*
 * PotentialField.c
 * Created on: Aug 26, 2021 07:25
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "PotentialField/PotentialField.h"

// private struct
typedef struct {
  float x;
  float y;
} PotentialFieldDirection;

// private function
PotentialFieldOutput CalculatePotentialField(PotentialFieldInstance *instance,
                                             PotentialFieldInput input) {
  double min_att_pot = 0.5;

  float sensor_distance;
  float sensor_threshold;
  float sensor_direction;

  PotentialFieldDirection rep_pot;
  rep_pot.x = 0;
  printf("rep_pot.x ");
  for (uint8_t i = 0; i < instance->num_sensor; ++i) {
    sensor_distance = *(input.sensor_distance + i);
    sensor_threshold = *(input.sensor_threshold + i);
    sensor_direction = *(input.sensor_direction + i);
    if (sensor_distance <= instance->min_detectable_distance)
      sensor_distance = instance->min_detectable_distance + 0.1;
    if (sensor_distance <= sensor_threshold) {
      rep_pot.x +=
          (1.0 / pow(sensor_distance - instance->min_detectable_distance, 2) *
           cos(input.theta + sensor_direction));
      printf(" %.2f ",
             instance->rep_scaling /
                 pow(sensor_distance - instance->min_detectable_distance, 2) *
                 cos(input.theta + sensor_direction));
    }
  }
  // printf(" ->total rep_pot.x = %.2f\n", rep_pot.x * instance->rep_scaling);

  rep_pot.y = 0;
  printf("rep_pot.y ");
  for (uint8_t i = 0; i < instance->num_sensor; ++i) {
    sensor_distance = *(input.sensor_distance + i);
    sensor_threshold = *(input.sensor_threshold + i);
    sensor_direction = *(input.sensor_direction + i);
    if (sensor_distance <= instance->min_detectable_distance)
      sensor_distance = instance->min_detectable_distance + 0.1;
    if (sensor_distance <= sensor_threshold) {
      rep_pot.y +=
          (1.0 / pow(sensor_distance - instance->min_detectable_distance, 2) *
           sin(input.theta + sensor_direction));
      printf(" %.2f ", instance->rep_scaling / pow(sensor_distance - 20.0, 2) *
                           sin(input.theta + sensor_direction));
    }
  }

  printf(" ->total rep_pot.y = %.2f\n", rep_pot.y);

  PotentialFieldDirection att_pot;

  att_pot.x = 0;
  att_pot.x = fmax(pow((1.0 / input.distance_goal), 2), min_att_pot) *
              cos(input.angle_goal) * instance->att_scaling;
  printf("att_pot.x = %.2f ", att_pot.x);

  att_pot.y = 0;
  att_pot.y = fmax(pow((1.0 / input.distance_goal), 2), min_att_pot) *
              sin(input.angle_goal) * instance->att_scaling;

  printf("att_pot.y = %.2f\n", att_pot.y);

  PotentialFieldDirection tot_pot;
  tot_pot.x = att_pot.x - (instance->rep_scaling * rep_pot.x);
  tot_pot.y = att_pot.y - (instance->rep_scaling * rep_pot.y);

  printf("tot_pot x = %.2f ", tot_pot.x);
  printf("tot_pot_y = %.2f\n", tot_pot.y);

  float res_theta = atan2(input.speed * cos(input.theta) + tot_pot.x,
                          input.speed * sin(input.theta) + tot_pot.y) -
                    input.theta;
  printf("res_theta = %.2f\n", res_theta);
  while (res_theta > M_PI) {
    res_theta -= 2 * M_PI;
  }
  while (res_theta < -M_PI) {
    res_theta += 2 * M_PI;
  }
  printf("res_theta = %.2f\n", res_theta);
  res_theta = fmin(instance->max_turn, res_theta);
  printf("res_theta = %.2f\n", res_theta);
  res_theta = fmax(-instance->max_turn, res_theta);
  printf("res_theta = %.2f\n", res_theta);

  float speed = sqrt((input.speed * sin(input.theta) + tot_pot.y) *
                         (input.speed * sin(input.theta) + tot_pot.y) +
                     (input.speed * cos(input.theta) + tot_pot.x) *
                         (input.speed * cos(input.theta) + tot_pot.x));
  printf("speed = %.2f\n", speed);
  speed = fmin(input.speed + instance->max_accel, speed);
  float res_speed = fmax(input.speed - instance->max_accel, speed);
  res_speed = fmin(res_speed, instance->max_speed);
  res_speed = fmax(res_speed, 0.0);
  PotentialFieldOutput output;
  output.res_speed = res_speed;
  output.res_theta = res_theta;
  return output;
}

// public function
bool InitPotentialField(PotentialFieldInstance *instance) {
  if (instance->rep_scaling < 0)
    instance->rep_scaling = fabs(instance->rep_scaling);

  if (instance->att_scaling < 0)
    instance->att_scaling = fabs(instance->att_scaling);

  if (instance->num_sensor == 0) return false;

  while (instance->max_turn > M_PI) {
    instance->max_turn -= 2 * M_PI;
  }
  while (instance->max_turn < -M_PI) {
    instance->max_turn += 2 * M_PI;
  }

  return true;
}

PotentialFieldOutput PotentialFieldLoop(PotentialFieldInstance *instance,
                                        PotentialFieldInput input) {
  PotentialFieldOutput output;
  output = CalculatePotentialField(instance, input);
  printf("res_speed %.2f\n", output.res_speed);
  printf("res_theta %.2f\n", output.res_theta);
  return output;
}