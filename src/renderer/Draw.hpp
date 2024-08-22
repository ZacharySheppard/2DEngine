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
  bool operator()(std::vector<Vertex> vertices);

 private:
  Program program_;
};
