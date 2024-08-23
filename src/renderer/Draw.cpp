#include "Draw.hpp"

#include <ranges>

namespace views = std::views;

DrawQuad::DrawQuad() noexcept {
  const auto fs = makeShader(ShaderType::Fragment, "assets/shaders/fragment.GLSL");
  program_.attach(fs);
  const auto vs = makeShader(ShaderType::Vertex, "assets/shaders/vertex.GLSL");
  program_.attach(vs);
  program_.link();
}

bool DrawQuad::operator()(std::vector<Vertex> vertices) {
  const auto vao = VertexArray();
  const auto positions = VertexBuffer(vertices | views::transform(&Vertex::pos));
  const auto colors = VertexBuffer(vertices | views::transform(&Vertex::col));

  constexpr auto quadIndices = std::array<uint32_t, 6>{0, 1, 2, 0, 2, 3};
  const auto indexBuffer = IndexBuffer(quadIndices);

  const uint32_t positionLocation = program_.attribute("vPos");
  const uint32_t colorLocation = program_.attribute("vCol");

  vao.bind();
  vao.addBuffer(positions, positionLocation);
  vao.addBuffer(colors, colorLocation);
  indexBuffer.bind();

  program_.bind();
  glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT, (void*)0);
  return true;
}