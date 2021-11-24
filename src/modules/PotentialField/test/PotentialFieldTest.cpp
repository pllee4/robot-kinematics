/*
 * PotentialFieldTest.cpp
 * Created on: Aug 26, 2021 20:48
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "gtest/gtest.h"

#include <math.h>
#include "PotentialField/PotentialField.h"

PotentialFieldInstance potential_field_instance;

TEST(PotentialField, Initialization) {
  EXPECT_FALSE(InitPotentialField(&potential_field_instance));
  potential_field_instance.rep_scaling = 1000;
  potential_field_instance.num_sensor = 4;
  potential_field_instance.min_detectable_distance = 20;
  EXPECT_TRUE(InitPotentialField(&potential_field_instance));
}

TEST(PotentialField, GetRepulsivePotentialField) {
  potential_field_instance.rep_scaling = 1000;
  potential_field_instance.num_sensor = 4;
  potential_field_instance.min_detectable_distance = 20;
  InitPotentialField(&potential_field_instance);

  float sensor_distance[4] = {1000.0, 1000.0, 1000.0, 1000.0};
  float sensor_direction[4] = {M_PI / 6.0f, 0, 0, -M_PI / 6.0f};
  float sensor_threshold[4] = {120.0, 120.0, 120.0, 120.0};

  PotentialFieldInput potential_input;

  potential_input.sensor_distance = sensor_distance;
  potential_input.sensor_direction = sensor_direction;
  potential_input.sensor_threshold = sensor_threshold;

  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input).x,
      0.0);
  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input).y,
      0.0);
  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input)
          .total,
      0.0);

  sensor_distance[0] = 1000.0;
  sensor_distance[1] = 30.0;
  sensor_distance[2] = 1000.0;
  sensor_distance[3] = 1000.0;

  potential_input.sensor_distance = sensor_distance;

  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input).x,
      10.0);
  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input).y,
      0.0);
  EXPECT_FLOAT_EQ(
      GetRepulsivePotentialField(&potential_field_instance, potential_input)
          .total,
      10.0);
}