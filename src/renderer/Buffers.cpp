#include "Buffers.hpp"

VertexBuffer::VertexBuffer() noexcept : id_(0), size_(0), length_(0) { glGenBuffers(1, &id_); }
void VertexBuffer::bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id_); }
uint32_t VertexBuffer::size() const noexcept {return size_;}
uint32_t VertexBuffer::length() const noexcept {return length_;}
VertexArray::VertexArray() noexcept {
    glGenVertexArrays(1, &id_);
}

void VertexArray::bind() const noexcept { glBindVertexArray(id_);}

void VertexArray::addBuffer(const VertexBuffer& buffer, uint32_t location) const noexcept {
  buffer.bind();
  const uint32_t componentCount = buffer.size() / buffer.length() / sizeof(GL_FLOAT);
  glEnableVertexAttribArray(location);
  glVertexAttribPointer(location, componentCount, GL_FLOAT, GL_FALSE, 0, nullptr);
}