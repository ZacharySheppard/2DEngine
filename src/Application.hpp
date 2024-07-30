#pragma once
#include "Window.hpp"

class Application {
 public:
  Application(Window window);
  bool run() const noexcept;

 private:
  Window window_;
};
