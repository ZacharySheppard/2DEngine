#pragma once

#include <string>

#include "Primitives.hpp"
#include "imgui.h"

class Panel {
 public:
  virtual ~Panel() = default;
  virtual void resize(Size size) noexcept = 0;
  virtual void move(Point topleft) noexcept = 0;
  virtual Size size() const noexcept = 0;
  virtual Point position() const noexcept = 0;
  virtual void update() noexcept = 0;
};