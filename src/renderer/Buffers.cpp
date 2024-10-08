#include "Buffers.hpp"

VertexBuffer::VertexBuffer() noexcept : id_(0), size_(0), length_(0) { glGenBuffers(1, &id_); }

VertexBuffer::~VertexBuffer() {
  if (id_ > 0) {
    glDeleteBuffers(1, &id_);
  }
}

void VertexBuffer::bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id_); }

uint32_t VertexBuffer::size() const noexcept { return size_; }

uint32_t VertexBuffer::length() const noexcept { return length_; }

IndexBuffer::IndexBuffer() noexcept : id_(0) { glGenBuffers(1, &id_); }

void IndexBuffer::bind() const noexcept { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }

IndexBuffer::~IndexBuffer() {
  if (id_ > 0) {
    glDeleteBuffers(1, &id_);
  }
}

uint32_t IndexBuffer::size() const noexcept { return size_; }

uint32_t IndexBuffer::length() const noexcept { return length_; }

VertexArray::VertexArray() noexcept { glGenVertexArrays(1, &id_); }

VertexArray::~VertexArray() {
  if (id_ > 0) {
    glDeleteVertexArrays(1, &id_);
  }
}
void VertexArray::bind() const noexcept { glBindVertexArray(id_); }

void VertexArray::addBuffer(const VertexBuffer& buffer, uint32_t location) const noexcept {
  buffer.bind();
  const uint32_t componentCount = buffer.size() / buffer.length() / sizeof(GL_FLOAT);
  glEnableVertexAttribArray(location);
  glVertexAttribPointer(location, componentCount, GL_FLOAT, GL_FALSE, 0, nullptr);
}

FrameBuffer::FrameBuffer() noexcept : id_(0) { glGenFramebuffers(1, &id_); }

FrameBuffer::~FrameBuffer() noexcept { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void FrameBuffer::bind() const noexcept { glBindFramebuffer(GL_FRAMEBUFFER, id_); }

RenderBuffer::RenderBuffer(float width, float height) noexcept : id_(0) {
  glGenRenderbuffers(1, &id_);
  bind();
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void RenderBuffer::attachFrameBuffer(const FrameBuffer& fb) const noexcept {
  fb.bind();
  bind();
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id_);
}

void RenderBuffer::bind() const noexcept { glBindRenderbuffer(GL_RENDERBUFFER, id_); }