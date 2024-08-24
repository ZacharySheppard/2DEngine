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
class OpenGLRenderPanel : public Panel {
 public:
  OpenGLRenderPanel(std::string name, Size size, Point position) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  [[nodiscard]] Size size() const noexcept override;
  [[nodiscard]] Point position() const noexcept override;
  void update() noexcept override;

  std::vector<Vertex> vertices = {{{-0.5f, -0.5f}, {0.f, 0.f, 0.f}},  // bottom left
                                  {{0.5f, -0.5f}, {1.f, 0.f, 0.f}},   // bottom right
                                  {{0.5f, 0.5f}, {0.f, 0.f, 1.f}},    // top right
                                  {{-0.5f, 0.5f}, {1.f, 1.f, 1.f}}};  // top left
  glm::vec3 bgColor;

 private:
  void updateCameraPosition();
  Point position_;
  DrawQuad drawQuad_;
  OrthographicCamera camera_;
  Size size_;
  std::string name_;
  Texture2D texture_;
  RenderBuffer rbo_;
  glm::vec3 cameraPosition_;
  std::jthread handleMouseEvents_;
};
