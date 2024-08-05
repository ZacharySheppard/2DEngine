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

 public:
  ImVec2 Offset = {0.0f, 0.0f};
  ImVec4 ColorBG = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
  ImVec4 ColorV3 = ImVec4(1.00f, 0.f, 0.0f, 1.00f);
  ImVec4 ColorV2 = ImVec4(0.f, 1.0f, 0.f, 1.00f);
  ImVec4 ColorV1 = ImVec4(0.f, 0.f, 1.f, 1.00f);

 private:
  Point position_;
  Size size_;
  std::string name_;
};