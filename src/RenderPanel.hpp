#pragma once
#include <glm/glm.hpp>

#include "Panel.hpp"
#include "glad/glad.h"
#include "renderer/Buffers.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

struct Vertex {
  glm::vec2 pos;
  glm::vec3 col;
};

class OpenGLRenderPanel : public Panel {
 public:
  OpenGLRenderPanel(std::string name, Size size, Point position) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  [[nodiscard]] Size size() const noexcept override;
  [[nodiscard]] Point position() const noexcept override;
  void update() noexcept override;

  std::vector<Vertex> vertices = {
      {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}}, {{0.6f, -0.4f}, {0.f, 1.f, 0.f}}, {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};
  glm::vec3 bgColor;

 private:
  Point position_;
  Size size_;
  std::string name_;
  Program program_;
  VertexArray array_;
  FrameBuffer fbo_;
  Texture2D texture_;
  RenderBuffer rbo_;
};
