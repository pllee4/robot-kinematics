/*
 * window.cpp
 * Created on: Sep 20, 2021 22:28
 * Description:
 *
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */

#include "window/window.hpp"

#include "window_impl.cpp"

namespace pllee4 {
namespace ui {
Window::Window(uint16_t width, uint16_t height, std::string title)
    : pimpl_(new impl(width, height, title)) {}

Window::~Window() = default;

bool Window::ShouldClose() { return pimpl_->ShouldClose(); }

void Window::StartFrame() { pimpl_->StartFrame(); }

void Window::RenderFrame() { pimpl_->RenderFrame(); }
}  // namespace ui
}  // namespace pllee4