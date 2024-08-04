#pragma once
#include "Panel.hpp"

class ConfigurationPanel : public Panel {
 public:
  ConfigurationPanel(std::string name, Size size, Point position = Point{0, 0}) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  Size size() const noexcept override;
  Point position() const noexcept override;
  void update() noexcept override;

 private:
  Point position_;
  Size size_;
  std::string name_;
  float f_ = 0.0f;
  int counter_ = 0;
  ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};