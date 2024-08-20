#pragma once
#include <logger/Logger.hpp>
#include <vector>

#include "Buffers.hpp"
class Texture2D {
 public:
  Texture2D(float width, float height) noexcept;
  void attachFrameBuffer(const FrameBuffer& fb) const noexcept;
  uint32_t id() const noexcept;
  void bind() const noexcept;

 private:
  uint32_t id_;
};