#pragma once
#include <memory>
#include <vector>

#include "Panel.hpp"
class HorizontalLayout {
 public:
  bool addPanel(Panel& panel) noexcept;

 private:
  Point lastStart_{0, 0};
};

class VerticalLayout {
 public:
  bool addPanel(Panel& panel) noexcept;

 private:
  Point lastStart_{0, 0};
};