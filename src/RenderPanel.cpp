#include "RenderPanel.hpp"

#include <ranges>
#include <vector>

#include "logger/Logger.hpp"
namespace {
namespace ranges = std::ranges;
namespace views = std::views;
}  // namespace

OpenGLRenderPanel::OpenGLRenderPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {
  // TODO load from source file, update cmake

  const auto fs = makeShader(ShaderType::Fragment, "assets/shaders/fragment.GLSL");
  program_.attach(fs);
  const auto vs = makeShader(ShaderType::Vertex, "assets/shaders/vertex.GLSL");
  program_.attach(vs);
  program_.link();

  fbo_.bind();
  texture_.configure(size_.width, size_.height);
  rbo_.configure(size_.width, size_.height);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    logger::info("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
void OpenGLRenderPanel::update() noexcept {
  auto v = std::vector<Vertex>(std::begin(vertices), std::end(vertices));
  auto positions = VertexBuffer(v | views::transform(&Vertex::pos));
  auto colors = VertexBuffer(v | views::transform(&Vertex::col));

  const uint32_t vpos_location = program_.attribute("vPos");
  const uint32_t vcol_location = program_.attribute("vCol");

  array_.bind();
  array_.addBuffer(positions, vpos_location);
  array_.addBuffer(colors, vcol_location);
  texture_.bind();

  fbo_.bind();
  rbo_.bind();

  glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, size_.width, size_.height);
  program_.bind();
  array_.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
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