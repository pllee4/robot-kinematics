/* 
 * DWA.h
 * Created on: Sep 27, 2021 07:10
 * Description: 
 * 
 * Reference:
 * [1] https://github.com/AtsushiSakai/PythonRobotics/blob/master/PathPlanning/DynamicWindowApproach/dynamic_window_approach.py
 * [2] https://github.com/CtfChan/LearnRoboticsCpp/blob/master/src/path_planning/dwa.cpp
 * 
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 

#ifndef DWA_H
#define DWA_H

typedef struct {
  float x;
  float y;
} Point;

typedef struct {
  int size;
  Point *points;
} Obstacles;

typedef struct {
  Point point;
  float yaw;
} Pose;

typedef struct {
  float x_min;
  float y_min;
  float x_max;
  float y_max;
} Base;

typedef struct {
    float max_speed; // m/s
    float min_speed; // m/s
    float max_yaw_rate; // rad/s
    float max_accel;
    float max_delta_yaw_rate; // rad/s^2
    float vel_resolution;
    float yaw_resolution;
    float dt;
    float predict_time;
    float alpha;
    float beta;
    float gamma;
    float stuck_constant;
    Base base;
} DWAConfig;

typedef struct {
  int num_possible_v;
  float *possible_v;
  int num_possible_w;
  float *possible_w;
} DynamicWindow;

typedef struct {
  float linear;
  float angular;
} Velocity;

float GetHeadingCost(Pose pose, Point goal);
float GetClearanceCost(Pose pose, Velocity velocity, Obstacles *obstacles, DWAConfig config);
float GetVelocityCost(Velocity velocity, Point goal);
Velocity DWAPlanning(Pose pose, Velocity vel, Point goal, DWAConfig config)

#endif /* DWA_H */
