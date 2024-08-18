#include "RenderPanel.hpp"

#include <vector>

#include "logger/Logger.hpp"
#include <ranges>
namespace {
namespace ranges = std::ranges;
namespace views = std::views;

const char* vertex_shader_text =
    "#version 330\n"
    "in vec3 vCol;\n"
    "in vec2 vPos;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(vPos, 0.0, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

const char* fragment_shader_text =
    "#version 330\n"
    "in vec3 color;\n"
    "out vec4 fragment;\n"
    "void main()\n"
    "{\n"
    "    fragment = vec4(color, 1.0);\n"
    "}\n";


}  // namespace

OpenGLRenderPanel::OpenGLRenderPanel(std::string name, Size size, Point position) noexcept
    : name_(name), position_(position), size_(size) {

  auto fs = loadFragmentShader(std::string{fragment_shader_text});
  program_.attach(fs);
  auto vs = loadVertexShader(std::string{vertex_shader_text});
  program_.attach(vs);
  program_.link();
  

  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size_.width, size_.height, 0, GL_RGB, 
  GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);

  glGenRenderbuffers(1, &rbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size_.width, size_.height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    logger::info("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
void OpenGLRenderPanel::update() noexcept {
  auto v = std::vector<Vertex>(std::begin(vertices), std::end(vertices));
  auto positions = VertexBuffer();
  positions.bind();
  std::vector<glm::vec2> pos;
  ranges::transform(v, std::back_inserter(pos), &Vertex::pos);
  positions.assign(pos);

  auto colors = VertexBuffer();
  colors.bind();
  std::vector<glm::vec3> col;
  ranges::transform(v, std::back_inserter(col), &Vertex::col);
  colors.assign(col);
  const uint32_t vpos_location = program_.attribute("vPos");
  const uint32_t vcol_location = program_.attribute("vCol");

  array_.bind();
  array_.addBuffer(positions, vpos_location);
  array_.addBuffer(colors, vcol_location);

  glBindTexture(GL_TEXTURE_2D, texture_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
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
  ImGui::Image((ImTextureID)texture_, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void OpenGLRenderPanel::move(Point topleft) noexcept { position_ = topleft; }
void OpenGLRenderPanel::resize(Size size) noexcept { size_ = size; }
Size OpenGLRenderPanel::size() const noexcept { return size_; }
Point OpenGLRenderPanel::position() const noexcept { return position_; }