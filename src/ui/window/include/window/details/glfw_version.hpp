/*
 * glfw_version.hpp
 * Created on: Feb 06, 2022 11:52
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#ifndef GLFW_VERSION_HPP
#define GLFW_VERSION_HPP

namespace pllee4 {

namespace backend {
struct UIBackend {
  static constexpr const char* glsl_version_ = "#version 130";
  static constexpr int glfw_context_version_major_ = 3;
  static constexpr int glfw_context_version_minor_ = 0;
};
}  // namespace backend
}  // namespace pllee4

#endif /* GLFW_VERSION_HPP */
