#pragma once
#include <iterator>
#include "logger/logger.hpp"
#include "glad/glad.h"
class VertexBuffer {
 public:
  VertexBuffer() noexcept;
  void bind() const noexcept;
  template <class Container>
  void assign(Container container) const noexcept {
    const auto length = std::ssize(container);
    if (length == 0) {
      logger::info("skipped buffer with 0 length")
      return;
    }
    const auto size = length * sizeof(*std::begin(container));
    glBufferData(GL_ARRAY_BUFFER, size, std::data(container), GL_STATIC_DRAW);
  }

 private:
  GLuint id_;
};

class IndexBuffer {
 public:
  void bind() const noexcept;

 private:
  GLuint id_;
};

class VertexArray {
 public:
  void bind() const noexcept;

 private:
  GLuint id_;
};
