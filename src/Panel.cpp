#include "Panel.hpp"

ConfigurationPanel::ConfigurationPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {}
void ConfigurationPanel::update() noexcept {
  ImGui::SetNextWindowSize({size_.width, size_.height});
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

void ConfigurationPanel::move(Point topleft) noexcept { position_ = topleft; }
void ConfigurationPanel::resize(Size size) noexcept { size_ = size; }
Size ConfigurationPanel::size() const noexcept { return size_; }
Point ConfigurationPanel::position() const noexcept { return position_; }

OpenGLRenderPanel::OpenGLRenderPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {}
void OpenGLRenderPanel::update() noexcept {
  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), 0, flags);
  ImGui::End();
}

void OpenGLRenderPanel::move(Point topleft) noexcept { position_ = topleft; }
void OpenGLRenderPanel::resize(Size size) noexcept { size_ = size; }
Size OpenGLRenderPanel::size() const noexcept { return size_; }
Point OpenGLRenderPanel::position() const noexcept { return position_; }