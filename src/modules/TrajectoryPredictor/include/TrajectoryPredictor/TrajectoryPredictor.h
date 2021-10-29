/* 
 * TrajectoryPredictor.h
 * Created on: Oct 18, 2021 21:26
 * Description: Curently only valid for differential model
 *
 *
 * Reference:
 * http://www.ladispe.polito.it/corsi/meccatronica/01CFI/2011-12/Slides/PR_2012_06-Robot%20motion.pdf
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 

#ifndef TRAJECTORYPREDICTOR_H
#define TRAJECTORYPREDICTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum { Euler = 0, RungeKutta } TrajectoryEstimationType;

typedef struct {
  float x;
  float y;
  float theta;
} TrajectoryPoint;

typedef struct {
  float sampling_time;
  float linear;
  float angular;
  TrajectoryPoint initial_points;
  TrajectoryEstimationType type;
} TrajectoryConfig;

void GetTrajectoryPoints(uint16_t num_of_points, TrajectoryPoint *points,
                         TrajectoryConfig config);

#ifdef __cplusplus
}
#endif

#endif /* TRAJECTORYPREDICTOR_H */
