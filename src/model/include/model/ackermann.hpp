/*
 * ackermann.hpp
 * Created on: Feb 06, 2022 18:08
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#ifndef ACKERMANN_HPP
#define ACKERMANN_HPP

#include <memory>

#include "display/display_base.hpp"

namespace pllee4 {
class Ackermann : public ui::DisplayBase {
 public:
  Ackermann();
  ~Ackermann();

  void Display() override;

 private:
  static constexpr uint16_t display_width = 1080;
  static constexpr uint16_t display_height = 720;
  class impl;
  std::unique_ptr<impl> pimpl_;
};
}  // namespace pllee4
#endif /* ACKERMANN_HPP */
