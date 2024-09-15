#include "SceneView.hpp"

#include <format>

SceneView::SceneView(Panel panel) noexcept : panel_(panel) {}
void SceneView::update() noexcept {
  const auto [width, height] = panel_.size();
  const auto [posx, posy] = panel_.position();
  ImGui::SetNextWindowSize({width, height});
  ImGui::SetNextWindowPos({posx, posy});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(panel_.name().c_str(), 0, flags);

  ImGui::End();
}
Panel& SceneView::display() noexcept { return panel_; }
