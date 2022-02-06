/*
 * display_base.cpp
 * Created on: Feb 06, 2022 17:01
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#include "display/display_base.hpp"

namespace pllee4 {
namespace ui {
DisplayBase::DisplayBase(uint16_t width, uint16_t height, std::string title) {
  window_ = std::make_unique<Window>(width, height, title);
}
void DisplayBase::ShowDisplay() {
  while (!window_->ShouldClose()) {
    window_->StartFrame();
    Display();  // to be overriden
    window_->RenderFrame();
  }
}
}  // namespace ui
}  // namespace pllee4