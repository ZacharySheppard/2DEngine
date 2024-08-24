#pragma once
#include <glm/glm.hpp>
class OrthographicCamera {
 public:
  OrthographicCamera(uint32_t width, uint32_t height);
  [[nodiscard]] glm::mat4 mvp() const noexcept;
  void setTarget(glm::vec3) noexcept;
  [[nodiscard]] glm::vec3 target() const noexcept;
  void setZoom(float zoom) noexcept;
  [[nodiscard]] float zoom() const noexcept;

 private:
  float zoom_;
  float aspectRatio_;
  glm::vec3 target_;
  glm::mat4 view_;
  glm::mat4 proj_;
};