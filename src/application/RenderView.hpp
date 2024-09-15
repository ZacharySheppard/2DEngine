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

class OpenGLRenderView {
 public:
  OpenGLRenderView(Panel panel) noexcept;
  Panel& display() noexcept;
  void update() noexcept;
  glm::vec3 bgColor;

 private:
  void updateCameraPosition();
  Panel panel_;
  Grid grid_;
  DrawQuad drawQuad_;
  DrawLine drawLine_;
  OrthographicCamera camera_;
  Texture2D texture_;
  RenderBuffer rbo_;
};
