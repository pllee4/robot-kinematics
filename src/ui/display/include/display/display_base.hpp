/*
 * display_base.hpp
 * Created on: Feb 06, 2022 16:56
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#ifndef DISPLAY_BASE_HPP
#define DISPLAY_BASE_HPP

#include <memory>

#include "window/window.hpp"

namespace pllee4 {
namespace ui {
class DisplayBase {
 public:
  DisplayBase(uint16_t width = 640, uint16_t height = 480,
              std::string title = "Display");
  virtual ~DisplayBase() = default;

  void ShowDisplay();
  virtual void Display() {}

 private:
  std::unique_ptr<Window> window_;
};
}  // namespace ui
}  // namespace pllee4

#endif /* DISPLAY_BASE_HPP */
