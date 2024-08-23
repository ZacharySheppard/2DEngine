#include "RenderPanel.hpp"

#include <ranges>
#include <vector>

#include "logger/Logger.hpp"
namespace {
namespace ranges = std::ranges;
namespace views = std::views;
}  // namespace

OpenGLRenderPanel::OpenGLRenderPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size), rbo_(size.width, size.height), texture_(size.width, size.height) {}

void OpenGLRenderPanel::update() noexcept {
  {
    const auto framebuffer = FrameBuffer();
    texture_.attachFrameBuffer(framebuffer);
    rbo_.attachFrameBuffer(framebuffer);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      logger::info("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    texture_.bind();
    framebuffer.bind();
    rbo_.bind();
    glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, size_.width, size_.height);
    drawQuad_(vertices);
  }

  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), nullptr, flags);
  ImGui::Image((ImTextureID)texture_.id(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void OpenGLRenderPanel::move(Point topleft) noexcept { position_ = topleft; }
void OpenGLRenderPanel::resize(Size size) noexcept { size_ = size; }
Size OpenGLRenderPanel::size() const noexcept { return size_; }
Point OpenGLRenderPanel::position() const noexcept { return position_; }