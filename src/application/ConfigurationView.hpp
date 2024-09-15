#pragma once
#include "Panel.hpp"

class ConfigurationView {
 public:
  ConfigurationView(Panel display) noexcept;
  void update() noexcept;
  Panel& display() noexcept;

 public:
  ImVec2 Offset = {0.0f, 0.0f};
  ImVec4 ColorBG = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
  ImVec4 ColorV3 = ImVec4(1.00f, 0.f, 0.0f, 1.00f);
  ImVec4 ColorV2 = ImVec4(0.f, 1.0f, 0.f, 1.00f);
  ImVec4 ColorV1 = ImVec4(0.f, 0.f, 1.f, 1.00f);

 private:
  Panel panel_;
};