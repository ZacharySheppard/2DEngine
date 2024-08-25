#pragma once
#include <array>
#include <glm/glm.hpp>

#include "Buffers.hpp"
#include "Shader.hpp"

struct Vertex {
  glm::vec2 pos;
  glm::vec3 col;
};

struct DrawQuad {
  DrawQuad() noexcept;
  bool operator()(std::vector<Vertex> vertices, glm::mat4 mvp);

 private:
  Program program_;
};

struct DrawLine {
  DrawLine() noexcept;
  bool operator()(std::vector<Vertex> lines, glm::mat4 mvp);

 private:
  Program program_;
};
