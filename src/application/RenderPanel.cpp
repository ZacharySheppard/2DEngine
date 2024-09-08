#include "RenderPanel.hpp"

#include <format>
#include <ranges>
#include <vector>

#include "logger/Logger.hpp"
namespace {
namespace ranges = std::ranges;
namespace views = std::views;
}  // namespace

OpenGLRenderPanel::OpenGLRenderPanel(std::string name, Size size, Point position) noexcept
    : name_(name),
      position_(position),
      size_(size),
      rbo_(size.width, size.height),
      texture_(size.width, size.height),
      camera_(size.width, size.height) {
  grid_.recalculate(camera_);
}

void OpenGLRenderPanel::update() noexcept {
  {
    const auto framebuffer = FrameBuffer();
    texture_.attachFrameBuffer(framebuffer);
    rbo_.attachFrameBuffer(framebuffer);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      logger::error(" framebuffer is not complete.");
    texture_.bind();
    framebuffer.bind();
    rbo_.bind();
    glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, size_.width, size_.height);
    drawLine_(grid_.vertices(), camera_.mvp());
  }

  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), nullptr, flags);
  updateCameraPosition();
  ImGui::Image((ImTextureID)texture_.id(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void OpenGLRenderPanel::updateCameraPosition() {
  const auto zoom = camera_.zoom();
  auto hasChanged = false;
  if (ImGui::IsMouseDragging(0) && ImGui::IsWindowFocused()) {
    auto delta = ImGui::GetMouseDragDelta();
    const auto target = camera_.target();
    const auto aspectRatio = size_.width / size_.height;
    const auto diff = glm::vec3{(2.0f * zoom * aspectRatio * delta.x / size_.width),  // x
                                (2.0f * zoom * delta.y / size_.height),               // y
                                0.0f};                                                // z
    camera_.setTarget(target + diff);
    ImGui::ResetMouseDragDelta();
    hasChanged = true;
  }
  float delta = ImGui::GetIO().MouseWheel;
  if (ImGui::IsWindowFocused() && delta != 0) {
    camera_.setZoom(zoom + delta);
    hasChanged = true;
  }

  if (hasChanged) {
    grid_.recalculate(camera_);
  }
}

void OpenGLRenderPanel::move(Point topleft) noexcept { position_ = topleft; }
void OpenGLRenderPanel::resize(Size size) noexcept { size_ = size; }
Size OpenGLRenderPanel::size() const noexcept { return size_; }
Point OpenGLRenderPanel::position() const noexcept { return position_; }

void Grid::recalculate(const OrthographicCamera& cam) {
  const auto zoom = cam.zoom();
  const auto target = cam.target();
  const auto aspectRatio = cam.aspectRatio();
  const int maxX = zoom * aspectRatio;
  const int maxY = static_cast<int>(zoom);
  const auto divisionsX = std::views::iota(0, maxX + 1);
  const auto divisionsY = std::views::iota(0, maxY + 1);
  const auto color = glm::vec3{0.8f, 0.8f, 0.8f};
  const auto makeVertex = [color](glm::vec2 pos) { return Vertex{pos, color}; };
  vertices_ = std::vector<Vertex>();

  for (const auto division : divisionsX) {
    const float left = std::trunc(target.x - division);
    const float right = std::trunc(target.x + division);
    const float top = target.y + zoom;
    const float bottom = target.y - zoom;
    const auto vertices = std::vector{makeVertex({left, top}), makeVertex({left, bottom}), makeVertex({right, top}),
                                      makeVertex({right, bottom})};
    vertices_.append_range(vertices);
  }
  for (const auto division : divisionsY) {
    const float left = target.x - aspectRatio * zoom;
    const float right = target.x + aspectRatio * zoom;
    const float top = std::trunc(target.y + division);
    const float bottom = std::trunc(target.y - division);
    const auto vertices = std::vector{makeVertex({left, top}), makeVertex({right, top}), makeVertex({left, bottom}),
                                      makeVertex({right, bottom})};
    vertices_.append_range(vertices);
  }
}

std::vector<Vertex> Grid::vertices() const noexcept { return vertices_; }