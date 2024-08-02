#pragma once
#include <string>

#include "imgui.h"

struct Point {
  float x;
  float y;
};

class Panel {
 public:
  virtual ~Panel() = default;
  virtual void resize(Point size) noexcept = 0;
  virtual void move(Point topleft) noexcept = 0;
  virtual Point size() const noexcept = 0;
  virtual Point position() const noexcept = 0;
  virtual void update() noexcept = 0;
};

class DummyPanel : public Panel {
 public:
  DummyPanel(std::string name) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Point size) noexcept override;
  Point size() const noexcept override;
  Point position() const noexcept override;
  void update() noexcept override;

 private:
  Point position_;
  Point size_;
  std::string name_;
  float f_ = 0.0f;
  int counter_ = 0;
  ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
