#pragma once
#include "Panel.hpp"
#include "glad/glad.h"
class OpenGLRenderPanel : public Panel {
 public:
  OpenGLRenderPanel(std::string name, Size size, Point position) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  Size size() const noexcept override;
  Point position() const noexcept override;
  void update() noexcept override;

 private:
  Point position_;
  Size size_;
  std::string name_;
  GLuint program_;
  GLuint array_;
  GLuint fbo_;
  GLuint rbo_;
  GLuint texture_;
};
