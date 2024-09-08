#include "Draw.hpp"

#include <ranges>

#include "Camera.hpp"

namespace views = std::views;
namespace ranges = std::ranges;

DrawQuad::DrawQuad() noexcept {
  const auto fs = makeShader(ShaderType::Fragment, "assets/shaders/fragment.GLSL");
  program_.attach(fs);
  const auto vs = makeShader(ShaderType::Vertex, "assets/shaders/vertex.GLSL");
  program_.attach(vs);
  program_.link();
}

bool DrawQuad::operator()(std::vector<Vertex> vertices, glm::mat4 mvp) {
  const auto vao = VertexArray();
  const auto positions = VertexBuffer(vertices | views::transform(&Vertex::pos));
  const auto colors = VertexBuffer(vertices | views::transform(&Vertex::col));

  constexpr auto quadIndices = std::array<uint32_t, 6>{0, 1, 2, 0, 2, 3};
  auto indicies = std::vector<uint32_t>();
  const size_t numQuads = vertices.size() / 4;
  int offset = 0;
  for (auto i = 0; i < numQuads; i++) {
    ranges::transform(quadIndices, std::back_inserter(indicies), [offset](uint32_t i) { return i + offset; });
    offset += 4;
  }

  const auto indexBuffer = IndexBuffer(indicies);

  const uint32_t positionLocation = program_.attribute("vPos");
  const uint32_t colorLocation = program_.attribute("vCol");
  program_.uniform("mvp", mvp);

  vao.bind();
  vao.addBuffer(positions, positionLocation);
  vao.addBuffer(colors, colorLocation);
  indexBuffer.bind();

  program_.bind();
  glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT, (void*)0);
  return true;
}

DrawLine::DrawLine() noexcept {
  const auto fs = makeShader(ShaderType::Fragment, "assets/shaders/fragment.GLSL");
  program_.attach(fs);
  const auto vs = makeShader(ShaderType::Vertex, "assets/shaders/vertex.GLSL");
  program_.attach(vs);
  program_.link();
}

bool DrawLine::operator()(std::vector<Vertex> lines, glm::mat4 mvp) {
  const auto vao = VertexArray();
  const auto positions = VertexBuffer(lines | views::transform(&Vertex::pos));
  const auto colors = VertexBuffer(lines | views::transform(&Vertex::col));

  const uint32_t positionLocation = program_.attribute("vPos");
  const uint32_t colorLocation = program_.attribute("vCol");
  program_.uniform("mvp", mvp);

  vao.bind();
  vao.addBuffer(positions, positionLocation);
  vao.addBuffer(colors, colorLocation);

  program_.bind();
  glDrawArrays(GL_LINES, 0, lines.size());
  return true;
}