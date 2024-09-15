#include "RenderView.hpp"

#include <format>
#include <ranges>
#include <vector>

#include "logger/Logger.hpp"
namespace {
namespace ranges = std::ranges;
namespace views = std::views;
}  // namespace

OpenGLRenderView::OpenGLRenderView(Panel display) noexcept
    : rbo_(display.size().width, display.size().height),
      texture_(display.size().width, display.size().height),
      camera_(display.size().width, display.size().height),
      panel_(display) {
  grid_.recalculate(camera_);
}

void OpenGLRenderView::update() noexcept {
  const auto [width, height] = panel_.size();
  const auto [posx, posy] = panel_.position();
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
    glViewport(0, 0, width, height);
    drawLine_(grid_.vertices(), camera_.mvp());
  }

  ImGui::SetNextWindowSize({width, height});
  ImGui::SetNextWindowPos({posx, posy});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(panel_.name().c_str(), 0, flags);
  updateCameraPosition();
  ImGui::Image((ImTextureID)texture_.id(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void OpenGLRenderView::updateCameraPosition() {
  const auto [width, height] = panel_.size();
  const auto zoom = camera_.zoom();
  auto hasChanged = false;
  if (ImGui::IsMouseDragging(0) && ImGui::IsWindowFocused()) {
    auto delta = ImGui::GetMouseDragDelta();
    const auto target = camera_.target();
    const auto aspectRatio = width / height;
    const auto diff = glm::vec3{(2.0f * zoom * aspectRatio * delta.x / width),  // x
                                (2.0f * zoom * delta.y / height),               // y
                                0.0f};                                          // z
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

Panel& OpenGLRenderView::display() noexcept { return panel_; }

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