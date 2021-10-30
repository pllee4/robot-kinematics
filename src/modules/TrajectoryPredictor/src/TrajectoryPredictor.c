/*
 * TrajectoryPredictor.c
 * Created on: Oct 18, 2021 21:26
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "TrajectoryPredictor/TrajectoryPredictor.h"
#include <math.h>

// private function
float ComputeDistance(TrajectoryPoint *points) {
  return sqrt(pow((points[1].x - points[0].x), 2) +
              pow((points[1].y - points[0].y), 2));
}

void GetTrajectoryPoints(uint16_t num_of_points, TrajectoryPoint *points,
                         TrajectoryConfig config) {
  // prev_angular is ignored here
  float prev_angular = config.angular;

  // store initial point
  points[0].x = config.initial_points.x;
  points[0].y = config.initial_points.y;
  points[0].theta = config.initial_points.theta;

  if (config.type == Euler) {
    for (uint16_t i = 1; i < num_of_points; i++) {
      points[i].x = points[i - 1].x + config.linear * cos(points[i - 1].theta) *
                                          config.sampling_time;
      points[i].y = points[i - 1].y + config.linear * sin(points[i - 1].theta) *
                                          config.sampling_time;
      points[i].theta =
          points[i - 1].theta + prev_angular * config.sampling_time;
    }
  } else if (config.type == RungeKutta) {
    for (uint16_t i = 1; i < num_of_points; i++) {
      points[i].x = points[i - 1].x +
                    config.linear *
                        cos(points[i - 1].theta +
                            0.5 * config.angular * config.sampling_time) *
                        config.sampling_time;
      points[i].y = points[i - 1].y +
                    config.linear *
                        sin(points[i - 1].theta +
                            0.5 * config.angular * config.sampling_time) *
                        config.sampling_time;
      points[i].theta =
          points[i - 1].theta + prev_angular * config.sampling_time;
    }
  }
}

float GetFinalPointDistance(TrajectoryConfig config) {
  TrajectoryPoint trajectory_points[2];
  GetTrajectoryPoints(2, trajectory_points, config);
  return ComputeDistance(trajectory_points);
}