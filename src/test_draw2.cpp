#include <cairo.h>
#include <math.h>

#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>  // Initialize with gl3wInit()

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include "window/window.hpp"

#include <iostream>

using namespace pllee4;

int main(int, char**) {
  // Setup window
  Window window(1080, 720, "Robot kinematics simulator");

  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
  // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

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

    ImGui::Begin("Cairo Canvas", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoBackground);

    float y_translate;
    bool y_translate_up{false};
    bool y_translate_down{false};

    float turning = 0.0;

    // for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
    for (int i = 0x106; i < 0x10a; i++) {
      if (ImGui::IsKeyDown(i)) {
        if (i == 0x106) turning = 30 * M_PI / 180.0;     // right
        if (i == 0x107) turning = -30.0 * M_PI / 180.0;  // left
        if (i == 0x108) {                                // up
          if (!y_translate_up) y_translate_down = true;
          if (y_translate_down) y_translate += 2.0;
        }
        if (i == 0x109) {  // down
          if (!y_translate_down) y_translate_up = true;
          if (y_translate_up) y_translate -= 2.0;
        }
      }
      if (ImGui::IsKeyReleased(i)) {
        if (i == 0x108) y_translate_down = false;
        if (i == 0x109) y_translate_up = false;
      }
    }
    cairo_surface_t* cairo_surface = nullptr;
    cairo_t* cr = nullptr;
    cairo_surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 450.0, 300.0);
    cr = cairo_create(cairo_surface);

    float cx, cy;
    float front_wheel_width = 4.0;
    float front_wheel_height = 12.0;
    float rear_wheel_width = 5.5;
    float rear_wheel_height = 12.0;

    float front_wheel_left_pos = 100.0;

    float wheel_base = 45.0;
    float track_width = 30.0;
    cx = 0.0;
    cy = 0.0;

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_set_line_width(cr, 1.75);
    cairo_translate(cr, 150.0, 100);

    // translate whole body
    float speed;
    if (y_translate_up) {
      speed = 2.0;
    } else if (y_translate_down) {
      speed = -2.0;
    } else {
      speed = 0.0;
    }
    static float theta = 0.0;
    static float x = 0.0;
    static float y = 0.0;
    theta += speed * tan(turning) / wheel_base;
    y += speed * cos(theta);
    x += speed * sin(theta);

    // text for troubleshoot
    // ImGui::Text("speed: %f", speed);
    // ImGui::Text("sin(theta): %f", sin(theta));
    // ImGui::Text("cos(theta): %f", cos(theta));
    // ImGui::Text("theta: %f", theta);
    // ImGui::Text("x: %f", x);
    // ImGui::Text("y: %f", y);
    // cairo_translate(cr, 0.0, y_translate);
    cairo_translate(cr, x, -y);  // -y to move upwards

    if (fabs(theta) > 0.0) {
      cairo_translate(cr, front_wheel_width + track_width / 2.0, 0);
      cairo_rotate(cr, theta);
      cairo_translate(cr, -(front_wheel_width + track_width / 2.0), 0);
    }

    // front left wheel
    cairo_save(cr);
    // go to origin of rotation
    cairo_translate(cr, front_wheel_width / 2.0, front_wheel_height / 2.0);
    cairo_rotate(cr, turning);
    cairo_rectangle(cr, -front_wheel_width / 2.0, -front_wheel_height / 2.0,
                    front_wheel_width, front_wheel_height);
    cairo_restore(cr);

    // front horizontal line
    cx += front_wheel_width;
    cy += front_wheel_height / 2.0;
    cairo_move_to(cr, cx, cy);
    cx += track_width;
    cairo_line_to(cr, cx, cy);

    // front right wheel
    cairo_save(cr);
    // go to origin of rotation
    cairo_translate(cr,
                    front_wheel_width + track_width + front_wheel_width / 2.0,
                    front_wheel_height / 2.0);
    cairo_rotate(cr, turning);
    cairo_rectangle(cr, -front_wheel_width / 2.0, -front_wheel_height / 2.0,
                    front_wheel_width, front_wheel_height);
    cairo_restore(cr);

    // wheel base
    cx -= track_width / 2.0;
    cairo_move_to(cr, cx, cy);
    cy += wheel_base;
    cairo_line_to(cr, cx, cy);

    // rear left wheel
    cy -= rear_wheel_height / 2.0;
    cx -= track_width / 2.0;
    cairo_rectangle(cr, cx - rear_wheel_width, cy, rear_wheel_width,
                    rear_wheel_height);

    // rear horizontal line
    cy += rear_wheel_height / 2.0;
    cairo_move_to(cr, cx, cy);
    cx += track_width;
    cairo_line_to(cr, cx, cy);

    // rear right wheel
    cy -= rear_wheel_height / 2.0;
    cairo_rectangle(cr, cx, cy, rear_wheel_width, rear_wheel_height);
    cairo_stroke(cr);

    glBindTexture(GL_TEXTURE_2D, image_texture_);

    // convert surface to OpenGL texture
    unsigned char* data = cairo_image_surface_get_data(cairo_surface);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, 450, 300, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                 data);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    ImGui::Image((void*)(intptr_t)image_texture_,
                 ImGui::GetContentRegionAvail(), ImVec2(0, 0), ImVec2(1, 1),
                 ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 0.0));

    cairo_surface_destroy(cairo_surface);
    cairo_destroy(cr);

    ImGui::End();
    // Rendering
    window.RenderFrame();
  }

  return 0;
}