#pragma once

class Texture {
 public:
  virtual ~Texture() = default;
  virtual void bind() const noexcept = 0;
  virtual void attachFrameBuffer() = 0;
};

class Texture2D : public Texture {
 public:
  Texture2D() noexcept;
  void bind() const noexcept override;
  void attachFrameBuffer() override;
};