#include "Shader.hpp"

#include <fstream>
std::string loadFromFIle(fs::path path) {
  auto filestream = std::ifstream(path);
  std::stringstream buffer;
  buffer << filestream.rdbuf();
  return buffer.str();
}

uint32_t loadVertexShader(const std::string& source) {
  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  auto bytes = source.c_str();
  glShaderSource(vertexShader, 1, &bytes, nullptr);
  glCompileShader(vertexShader);
  return vertexShader;
}

uint32_t loadFragmentShader(const std::string& source) {
  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  auto bytes = source.c_str();
  glShaderSource(fragmentShader, 1, &bytes, nullptr);
  glCompileShader(fragmentShader);
  return fragmentShader;
}

Program::Program() noexcept : id_(glCreateProgram()) {}
void Program::attach(uint32_t id) const noexcept { glAttachShader(id_, id); }
uint32_t Program::attribute(std::string name) const noexcept { return glGetAttribLocation(id_, name.c_str()); }
void Program::link() const noexcept { glLinkProgram(id_); }
void Program::bind() const noexcept { glUseProgram(id_); }