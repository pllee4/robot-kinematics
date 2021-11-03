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

using namespace pllee4;

int main(int, char**) {
  // Setup window
  Window window(1080, 720, "Trajectory Planning");

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

    float x_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float y_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ImPlot::CreateContext();
    if (ImPlot::BeginPlot("My Plot")) {
      ImPlot::PlotLine("My Line Plot", x_data, y_data, 10);
      ImPlot::EndPlot();
    }
    ImPlot::DestroyContext();

    ImGui::End();
    // Rendering
    window.RenderFrame();
  }

  return 0;
}