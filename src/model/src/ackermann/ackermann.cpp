/*
 * ackermann.cpp
 * Created on: Feb 06, 2022 18:15
 * Description:
 *
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */

#include "model/ackermann.hpp"

#include "ackermann_impl.cpp"

using namespace pllee4;

Ackermann::Ackermann()
    : DisplayBase(display_width, display_height, "Ackermann"),
      pimpl_(new impl) {}

Ackermann::~Ackermann() = default;

void Ackermann::Display() { pimpl_->Display(); }