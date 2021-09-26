/*
 * DWA.c
 * Created on: Sep 27, 2021 07:13
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include <math.h>

#include "DWA/DWA.h"

// private function
void CreateDynamicWindow(Velocity velocity, DWAConfig config,
                         DynamicWindow *dynamic_window) {
  float min_v =
      max(config.min_speed, velocity.linear - config.max_accel * config.dt);
  float maxV =
      min(config.max_speed, velocity.linear + config.max_accel * config.dt);
  float min_w = max(-config.max_yaw_rate,
                    velocity.angular - config.max_delta_yaw_rate * config.dt);
  float max_w = min(config.max_yaw_rate,
                    velocity.angular + config.max_delta_yaw_rate * config.dt);

  int num_possible_v = (maxV - min_v) / config.vel_resolution;
  int num_possible_w = (max_w - min_w) / config.yaw_resolution;

  dynamic_window->possible_v = malloc(num_possible_v * sizeof(float));
  dynamic_window->possible_w = malloc(num_possible_w * sizeof(float));
  dynamic_window->num_possible_v = num_possible_v;
  dynamic_window->num_possible_w = num_possible_w;

  for (int i = 0; i < num_possible_v; i++) {
    dynamic_window->possible_v[i] = min_v + (float)i * config.vel_resolution;
  }

  for (int i = 0; i < num_possible_w; i++) {
    dynamic_window->possible_w[i] = min_w + (float)i * config.yaw_resolution;
  }
}

void FreeDynamicWindow(DynamicWindow *dynamic_window) {
  free(dynamic_window->possible_v);
  free(dynamic_window->possible_w);
}

Obstacles *CreateObstacles(int size) {
  Obstacles *obstacles = malloc(sizeof(Obstacles));
  Obstacles->points = malloc(size * sizeof(Point));
  Obstacles->size = size;
  return Obstacles;
}

void FreeObstacles(Obstacles *Obstacles) {
  free(Obstacles->points);
  free(Obstacles);
}

Pose Motion(Pose pose, Velocity velocity, float dt) {
  Pose new_pose;
  new_pose.yaw = pose.yaw + velocity.angular * dt;
  new_pose.point.x = pose.point.x + velocity.linear * cos(new_pose.yaw) * dt;
  new_pose.point.y = pose.point.y + velocity.linear * sin(new_pose.yaw) * dt;
  return new_pose;
}

// public function

float GetHeadingCost(Pose pose, Point goal) {
  float dx = goal.x - pose.point.x;
  float dy = goal.y - pose.point.y;
  float angle_err = atan2(dy, dx);
  float angle_cost = angle_err - pose.yaw;
  return fabs(atan2(sin(angle_cost), cos(angle_cost)));
}

float GetClearanceCost(Pose pose, Velocity velocity, Obstacles *Obstacles,
                       DWAConfig config) {
  Pose pPose = pose;
  float time = 0.0;
  float minr = FLT_MAX;
  float r;
  float dx;
  float dy;

  float x;
  float y;

  while (time < config.predict_time) {
    pPose = Motion(pPose, velocity, config.dt);

    for (int i = 0; i < Obstacles->size; ++i) {
      dx = pPose.point.x - Obstacles->points[i].x;
      dy = pPose.point.y - Obstacles->points[i].y;
      x = -dx * cos(pPose.yaw) + -dy * sin(pPose.yaw);
      y = -dx * -sin(pPose.yaw) + -dy * cos(pPose.yaw);
      if (x <= config.base.x_max && x >= config.base.x_min &&
          y <= config.base.y_max && y >= config.base.y_min) {
        return FLT_MAX;
      }
      r = sqrtf(dx * dx + dy * dy);
      if (r < minr) minr = r;
    }
    time += config.dt;
  }
  return 1.0 / minr;
}

float GetVelocityCost(Velocity velocity, DWAConfig config) {
  return config.max_speed - velocity.linear;
}

Velocity DWAPlanning(Pose pose, Velocity velocity, Point goal,
                     Obstacles *Obstacles, DWAConfig config) {
  DynamicWindow dw;
  CreateDynamicWindow(velocity, config, &dw);
  Velocity pVelocity;
  Pose pPose = pose;
  float total_cost = FLT_MAX;
  float cost;
  Velocity bestVelocity;
  for (int i = 0; i < dw.num_possible_v; ++i) {
    for (int j = 0; j < dw.num_possible_w; ++j) {
      pPose = pose;
      pVelocity.linear = dw.possible_v[i];
      pVelocity.angular = dw.possible_w[j];
      pPose = Motion(pPose, pVelocity, config.predict_time);
      cost =
          config.alpha * GetHeadingCost(pPose, goal) +
          config.beta * GetClearanceCost(pose, pVelocity, Obstacles, config) +
          config.gamma * GetVelocityCost(pVelocity, config);
      if (cost < total_cost) {
        total_cost = cost;
        bestVelocity = pVelocity;
      }
    }
  }
  FreeDynamicWindow(&dw);
  return bestVelocity;
}
