#pragma once
#include <glm/glm.hpp>
#include <thread>

#include "Panel.hpp"
#include "glad/glad.h"
#include "renderer/Buffers.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Draw.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

class Grid {
 public:
  void recalculate(const OrthographicCamera& camera);
  [[nodiscard]] std::vector<Vertex> vertices() const noexcept;

 private:
  std::vector<Vertex> vertices_;
};

class OpenGLRenderPanel : public Panel {
 public:
  OpenGLRenderPanel(std::string name, Size size, Point position) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  [[nodiscard]] Size size() const noexcept override;
  [[nodiscard]] Point position() const noexcept override;
  void update() noexcept override;
  glm::vec3 bgColor;

 private:
  void updateCameraPosition();
  Grid grid_;
  Point position_;
  Size size_;
  DrawQuad drawQuad_;
  DrawLine drawLine_;
  OrthographicCamera camera_;
  std::string name_;
  Texture2D texture_;
  RenderBuffer rbo_;
};
