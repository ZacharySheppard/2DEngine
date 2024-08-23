#pragma once

#include <glad/glad.h>

#include <expected>
#include <filesystem>
#include <functional>
#include <glm/glm.hpp>
#include <string_view>
namespace fs = std::filesystem;

enum class ParseError { FileNotFound };
enum class ShaderType { Fragment, Vertex };

uint32_t makeShader(ShaderType type, fs::path path);

class Program {
 public:
  Program() noexcept;
  void attach(uint32_t id) const noexcept;
  uint32_t attribute(std::string name) const noexcept;
  uint32_t uniform(std::string name, glm::mat4 value) const noexcept;
  void link() const noexcept;
  void bind() const noexcept;

 private:
  GLuint id_;
};