#include "RenderPanel.hpp"

#include "logger/Logger.hpp"
#include "renderer/Buffers.hpp"
namespace {

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
  GLuint vbo_;

  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  program_ = glCreateProgram();
  glAttachShader(program_, vertex_shader);
  glAttachShader(program_, fragment_shader);
  glLinkProgram(program_);

  const GLint vpos_location = glGetAttribLocation(program_, "vPos");
  const GLint vcol_location = glGetAttribLocation(program_, "vCol");

  glGenVertexArrays(1, &array_);
  glBindVertexArray(array_);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));

  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size_.width, size_.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const GLint vpos_location = glGetAttribLocation(program_, "vPos");
  const GLint vcol_location = glGetAttribLocation(program_, "vCol");

  glBindVertexArray(array_);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));

  glBindTexture(GL_TEXTURE_2D, texture_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, size_.width, size_.height);
  glUseProgram(program_);
  glBindVertexArray(array_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  ImGui::SetNextWindowSize({size_.width, size_.height});
  ImGui::SetNextWindowPos({position_.x, position_.y});
  auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;
  ImGui::Begin(name_.c_str(), 0, flags);
  ImGui::Image((ImTextureID)texture_, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::End();
}

void OpenGLRenderPanel::move(Point topleft) noexcept { position_ = topleft; }
void OpenGLRenderPanel::resize(Size size) noexcept { size_ = size; }
Size OpenGLRenderPanel::size() const noexcept { return size_; }
Point OpenGLRenderPanel::position() const noexcept { return position_; }