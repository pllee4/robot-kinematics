/* 
 * app_ackermann.cpp
 * Created on: Feb 09, 2022 07:41
 * Description: 
 * 
 * Copyright (c) 2022 Pin Loon Lee (pllee4)
 */ 

#include "model/ackermann.hpp"

using namespace pllee4;

int main(int, char**) {
  std::unique_ptr<Ackermann> ackermann = std::make_unique<Ackermann>();
  ackermann->ShowDisplay();
  return 0;
}