#pragma once

#include <string>

#include "Primitives.hpp"
#include "imgui.h"

class Panel {
 public:
  Panel(std::string name, Size size, Point position) noexcept;
  void resize(Size size) noexcept;
  void move(Point topleft) noexcept;
  void rename(std::string name) noexcept;
  std::string name() const noexcept;
  Size size() const noexcept;
  Point position() const noexcept;

 private:
  std::string name_;
  Point position_;
  Size size_;
};