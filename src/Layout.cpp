#include "Layout.hpp"

bool HorizontalLayout::addPanel(Panel& panel) noexcept {
  panel.move(lastStart_);
  auto [x, y] = panel.size();
  lastStart_ = Point{lastStart_.x + x, lastStart_.y};
  return true;
}

bool VerticalLayout::addPanel(Panel& panel) noexcept {
  panel.move(lastStart_);
  auto [_, y] = panel.size();
  lastStart_ = Point{lastStart_.x, lastStart_.y + y};
  return true;
}