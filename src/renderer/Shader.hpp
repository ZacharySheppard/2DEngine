#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <functional>
#include <string_view>
namespace fs = std::filesystem;
[[nodiscard]] std::string loadFromFile(fs::path path);

using ShaderLoader = std::function<uint32_t(const std::string& source)>();

uint32_t loadVertexShader(const std::string& source);
uint32_t loadFragmentShader(const std::string& source);
class Program {
 public:
  Program() noexcept;
  void attach(uint32_t id) const noexcept;
  uint32_t attribute(std::string name) const noexcept;
  void link() const noexcept;
  void bind() const noexcept;

 private:
  GLuint id_;
};