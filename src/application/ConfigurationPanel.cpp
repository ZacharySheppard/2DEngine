#include "ConfigurationPanel.hpp"

ConfigurationPanel::ConfigurationPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {}
void ConfigurationPanel::update() noexcept {
  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), 0, flags);
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

void ConfigurationPanel::move(Point topleft) noexcept { position_ = topleft; }
void ConfigurationPanel::resize(Size size) noexcept { size_ = size; }
Size ConfigurationPanel::size() const noexcept { return size_; }
Point ConfigurationPanel::position() const noexcept { return position_; }