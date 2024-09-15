#include "ConfigurationView.hpp"

ConfigurationView::ConfigurationView(Panel display) noexcept : panel_(display) {}
void ConfigurationView::update() noexcept {
  const auto [width, height] = panel_.size();
  const auto [posx, posy] = panel_.position();
  ImGui::SetNextWindowSize({width, height});
  ImGui::SetNextWindowPos({posx, posy});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(panel_.name().c_str(), 0, flags);
  ImGui::Text("This is some useful text.");
  ImGui::NewLine();
  ImGui::SliderFloat("Offset X", &Offset.x, -.5f, .5f);
  ImGui::SliderFloat("Offset Y", &Offset.y, -.5f, .5f);
  ImGui::NewLine();
  ImGui::ColorEdit3("Background", (float*)&ColorBG);
  ImGui::NewLine();
  ImGui::ColorEdit3("V1 color", (float*)&ColorV1);
  ImGui::ColorEdit3("V2 color", (float*)&ColorV2);
  ImGui::ColorEdit3("V3 color", (float*)&ColorV3);
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Text("60 Frame Average %.1f FPS", io.Framerate);
  ImGui::End();
}

Panel& ConfigurationView::display() noexcept { return panel_; }