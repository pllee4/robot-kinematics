/*
 * window_impl.cpp
 * Created on: Feb 06, 2022 15:05
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window/details/glfw_version.hpp"
#include "window/window.hpp"

namespace pllee4 {
using namespace backend;
class Window::impl {
  static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
  }

 public:
  impl(uint16_t width, uint16_t height, std::string title) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                   UIBackend::glfw_context_version_major_);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                   UIBackend::glfw_context_version_minor_);

    // Create window with graphics context
    glfw_window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (glfw_window_ == NULL) {
      throw std::runtime_error("Failed to initialize GLFW library");
    }

    glfwMakeContextCurrent(glfw_window_);
    glfwSwapInterval(1);  // Enable vsync

    if (gl3wInit() != 0) {
      throw std::runtime_error("Failed to initialize OpenGL loader!\n");
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfw_window_, true);
    ImGui_ImplOpenGL3_Init(UIBackend::glsl_version_);
  }

  ~impl() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(glfw_window_);
    glfwTerminate();
  }

  bool ShouldClose() { return glfwWindowShouldClose(glfw_window_); }

  void StartFrame() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void RenderFrame() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(glfw_window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color_.x, clear_color_.y, clear_color_.z,
                 clear_color_.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(glfw_window_);
  }

 private:
  GLFWwindow *glfw_window_;

  ImVec4 clear_color_ = ImVec4(0.0f, 0.0f, 0.0f, 0.10f);
};
}  // namespace pllee4