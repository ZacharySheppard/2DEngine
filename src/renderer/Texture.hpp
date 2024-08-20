#pragma once
#include <logger/Logger.hpp>
#include <vector>

class FrameBufferTexture2D {
 public:
  FrameBufferTexture2D() noexcept;
  void configure(float width, float height) const noexcept;
  uint32_t id() const noexcept;
  void bind() const noexcept;

 private:
  uint32_t id_;
};