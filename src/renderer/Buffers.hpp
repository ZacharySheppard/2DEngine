#pragma once
#include <array>
#include <iterator>
#include <ranges>
#include <vector>

#include "glad/glad.h"
#include "logger/logger.hpp"
class VertexBuffer {
 public:
  VertexBuffer() noexcept;

  template <class Container>
  VertexBuffer(Container container) noexcept : VertexBuffer() {
    bind();
    length_ = std::ssize(container);
    if (length_ == 0) {
      logger::info("skipped buffer with 0 length");
      return;
    }
    size_ = length_ * sizeof(*std::ranges::begin(container));
    const auto data = std::vector(std::begin(container), std::end(container));
    glBufferData(GL_ARRAY_BUFFER, size_, std::ranges::data(data), GL_STATIC_DRAW);
  }

  ~VertexBuffer();
  void bind() const noexcept;
  [[nodiscard]] uint32_t size() const noexcept;
  [[nodiscard]] uint32_t length() const noexcept;
  template <std::ranges::input_range R>
  void assign(R container) noexcept {
    length_ = std::ssize(container);
    if (length_ == 0) {
      logger::info("skipped buffer with 0 length");
      return;
    }
    size_ = length_ * sizeof(*std::begin(container));
    const auto data = std::vector(std::begin(container), std::end(container));
    glBufferData(GL_ARRAY_BUFFER, size_, std::ranges::data(data), GL_STATIC_DRAW);
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

class FrameBuffer {
 public:
  FrameBuffer() noexcept;
  void bind() const noexcept;

 private:
  uint32_t id_;
};

class RenderBuffer {
 public:
  RenderBuffer(float width, float height) noexcept;
  void attachFrameBuffer(const FrameBuffer& fb) const noexcept;
  void bind() const noexcept;

 private:
  uint32_t id_;
};
