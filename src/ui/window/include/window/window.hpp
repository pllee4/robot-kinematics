/*
 * window.hpp
 * Created on: Sep 20, 2021 22:28
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <GLFW/glfw3.h>

namespace pllee4 {

class Window {
 public:
  Window(uint16_t width = 640, uint16_t height = 480,
         std::string title = "GUI Window");
  ~Window();

  bool ShouldClose();
  void StartFrame();
  void RenderFrame();

 private:
  GLFWwindow* glfw_window_;

  ImVec4 clear_color_ = ImVec4(0.0f, 0.0f, 0.0f, 0.10f);
};
}  // namespace pllee4
#endif /* WINDOW_HPP */
