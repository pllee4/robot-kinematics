/*
 * window.hpp
 * Created on: Sep 20, 2021 22:28
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <string>

namespace pllee4 {
namespace ui {
class Window {
 public:
  Window(uint16_t width = 640, uint16_t height = 480,
         std::string title = "GUI Window");
  ~Window();

  bool ShouldClose();
  void PollEvent();
  void StartFrame();
  void RenderFrame();

 private:
  class impl;
  std::unique_ptr<impl> pimpl_;
};
}  // namespace ui
}  // namespace pllee4
#endif /* WINDOW_HPP */
