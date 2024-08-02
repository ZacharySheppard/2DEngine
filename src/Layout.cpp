#include "Layout.hpp"

HorizontalLayout::HorizontalLayout(Point size, Point position) noexcept
    : size_(size), position_(position), lastStart_(position) {}

bool HorizontalLayout::addPanel(Panel& panel) noexcept {
  panel.move(lastStart_);
  auto [x, y] = panel.size();
  lastStart_ = Point{lastStart_.x + x, lastStart_.y};
  return true;
}

VerticalLayout::VerticalLayout(Point size, Point position) noexcept
    : size_(size), position_(position), lastStart_(position) {}

bool VerticalLayout::addPanel(Panel& panel) noexcept {
  panel.move(lastStart_);
  auto [_, y] = panel.size();
  lastStart_ = Point{lastStart_.x, lastStart_.y + y};
  return true;
}