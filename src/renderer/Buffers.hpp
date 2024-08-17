#pragma once
#include <iterator>
#include "logger/logger.hpp"
#include "glad/glad.h"
class VertexBuffer {
 public:
  VertexBuffer() noexcept;
  void bind() const noexcept;
  [[nodiscard]] uint32_t size() const noexcept;
  [[nodiscard]] uint32_t length() const noexcept;
  template <class Container>
  void assign(Container container) noexcept {
    length_ = std::ssize(container);
    if (length_ == 0) {
      logger::info("skipped buffer with 0 length");
      return;
    }
    size_ = length_ * sizeof(*std::begin(container));
    glBufferData(GL_ARRAY_BUFFER, size_, std::data(container), GL_STATIC_DRAW);
  }

 private:
  uint32_t size_;
  uint32_t length_;
  uint32_t id_;
};

class IndexBuffer {
 public:
  void bind() const noexcept;

 private:
  GLuint id_;
};

class VertexArray {
 public:
  VertexArray() noexcept;
  void bind() const noexcept;
  void addBuffer(const VertexBuffer& buffer, uint32_t location) const noexcept;

 private:
  uint32_t id_;
};
