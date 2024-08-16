#include "Buffers.hpp"

VertexBuffer::VertexBuffer() noexcept { glGenBuffers(1, &id_); }
void VertexBuffer::bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id_); }