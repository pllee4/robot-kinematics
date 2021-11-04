/*
 * test_plot.cpp
 * Created on: Nov 03, 2021 21:49
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include <cairo.h>
#include <math.h>

#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"

#include <GL/gl3w.h>  // Initialize with gl3wInit()

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include "TrajectoryPredictor/TrajectoryPredictor.h"
#include "window/window.hpp"

#include <iostream>
#include <vector>

using namespace pllee4;

int main(int, char**) {
  // Setup window
  auto constexpr window_width = 1080;
  auto constexpr window_height = 960;
  Window window(window_width, window_height, "Trajectory Response");

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  // Our sta
  ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.10f);
  GLuint image_texture_;

  glGenTextures(1, &image_texture_);
  glBindTexture(GL_TEXTURE_2D, image_texture_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // the following two are required on WebGL for non power-of-two textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  ImVec2 position;

  position.x = 0.0;
  position.y = 0.0;

  std::vector<float> x1_data, y1_data;
  std::vector<float> x2_data, y2_data;
  std::vector<float> x3_data, y3_data;

  x1_data.reserve(100);
  x2_data.reserve(100);
  x3_data.reserve(100);
  y1_data.reserve(100);
  y2_data.reserve(100);
  y3_data.reserve(100);

  for (uint32_t i = 1; i <= 100; ++i) {
    x1_data.push_back(i * 0.1);
    x2_data.push_back(i * 0.1);
    x3_data.push_back(i * 0.1);
  }

  for (uint32_t i = 0; i < 100; ++i) {
    y1_data.push_back(1 / x1_data[i]);          // 1 / x
    y2_data.push_back(1 / pow(x2_data[i], 2));  // 1 x^2
    y3_data.push_back(1 / exp(x3_data[i]));     // 1 / e^x
  }

  // Main loop
  while (!window.ShouldClose()) {
    glfwPollEvents();

    window.StartFrame();

    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin("Plotting", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoBackground);

    ImVec2 plot_size{window_width / 2.1, window_height / 3.5};

    ImPlot::CreateContext();
    if (ImPlot::BeginPlot("y = 1 / x", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y1_data[i] = (1 / x1_data[i]);
      }
      ImPlot::PlotLine("##NoTitle1", &x1_data[0], &y1_data[0], 100);
      ImPlot::EndPlot();
    }
    ImGui::SameLine();
    if (ImPlot::BeginPlot("y = 5 / x", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y1_data[i] = (5 / x1_data[i]);
      }
      ImPlot::PlotLine("##NoTitle1", &x1_data[0], &y1_data[0], 100);
      ImPlot::EndPlot();
    }

    if (ImPlot::BeginPlot("y = 1 / (x ^ 2)", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y2_data[i] = (1 / pow(x2_data[i], 2));  // 1 x^2
      }
      ImPlot::PlotLine("##NoTitle2", &x2_data[0], &y2_data[0], 100);
      ImPlot::EndPlot();
    }
    ImGui::SameLine();
    if (ImPlot::BeginPlot("y = 1 / (x ^ 4)", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y2_data[i] = (1 / pow(x2_data[i], 4));  // 1 x^2
      }
      ImPlot::PlotLine("##NoTitle2", &x2_data[0], &y2_data[0], 100);
      ImPlot::EndPlot();
    }

    if (ImPlot::BeginPlot("y = 1 / exp(x)", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y3_data[i] = (1 / exp(x3_data[i]));
      }
      ImPlot::PlotLine("##NoTitle3", &x3_data[0], &y3_data[0], 100);
      ImPlot::EndPlot();
    }
    ImGui::SameLine();
    if (ImPlot::BeginPlot("y = exp(1 / x)", plot_size)) {
      ImPlot::SetupAxesLimits(0, 10, 0, 100);
      for (uint16_t i = 0; i < 100; ++i) {
        y3_data[i] = (exp(1 / x3_data[i]));
      }
      ImPlot::PlotLine("##NoTitle3", &x3_data[0], &y3_data[0], 100);
      ImPlot::EndPlot();
    }

    ImPlot::DestroyContext();

    ImGui::End();
    // Rendering
    window.RenderFrame();
  }

  return 0;
}