#pragma once
#include <memory>
#include <vector>

#include "Panel.hpp"
class HorizontalLayout {
 public:
  HorizontalLayout(Point size, Point position) noexcept;
  bool addPanel(Panel& panel) noexcept;

 private:
  std::vector<Point> positions_;
  Point lastStart_;
  Point size_;
  Point position_;
};

class VerticalLayout {
 public:
  VerticalLayout(Point size, Point position) noexcept;
  bool addPanel(Panel& panel) noexcept;

 private:
  std::vector<Point> positions_;
  Point lastStart_;
  Point size_;
  Point position_;
};