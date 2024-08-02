#include "Panel.hpp"

DummyPanel::DummyPanel(std::string name) noexcept : name_(name) {}
void DummyPanel::update() noexcept {
  ImGui::SetNextWindowSize({size_.x, size_.y});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), 0, flags);
  ImGui::Text("This is some useful text.");
  ImGui::SliderFloat("float", &f_, 0.0f, 1.0f);
  ImGui::ColorEdit3("clear color", (float*)&clear_color_);

  if (ImGui::Button("Button")) {
    counter_++;
  }
  ImGui::SameLine();
  ImGui::Text("counter = %d", counter_);
  ImGuiIO& io = ImGui::GetIO();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();
}

void DummyPanel::move(Point topleft) noexcept { position_ = topleft; }
void DummyPanel::resize(Point size) noexcept { size_ = size; }
Point DummyPanel::size() const noexcept { return size_; }
Point DummyPanel::position() const noexcept { return position_; }