#include "ScenePanel.hpp"

#include <format>

ScenePanel::ScenePanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {}
void ScenePanel::update() noexcept {
  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), 0, flags);
  ImGui::BeginGroup();

  ImGui::End();
}
void ScenePanel::move(Point topleft) noexcept { position_ = topleft; }
void ScenePanel::resize(Size size) noexcept { size_ = size; }
Size ScenePanel::size() const noexcept { return size_; }
Point ScenePanel::position() const noexcept { return position_; }
