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

struct Line {
  glm::vec2 pos;
  glm::vec3 color;
};

struct DrawLine {
  DrawLine() noexcept;
  bool operator()(std::vector<Line> lines);

 private:
  Program program_;
};
