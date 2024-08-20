#include "texture.hpp"

#include <glad/glad.h>

FrameBufferTexture2D::FrameBufferTexture2D() noexcept : id_(0) { glGenTextures(1, &id_); }

void FrameBufferTexture2D::configure(float width, float height) const noexcept {
  bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id_, 0);
}
uint32_t FrameBufferTexture2D::id() const noexcept { return id_; }
void FrameBufferTexture2D::bind() const noexcept { glBindTexture(GL_TEXTURE_2D, id_); }
