#pragma once
#include <glm/glm.hpp>
class OrthographicCamera {
 public:
  OrthographicCamera(uint32_t width, uint32_t height);
  [[nodiscard]] glm::mat4 mvp() const noexcept;
  void setCameraPosition(glm::vec3) noexcept;

 private:
  glm::mat4 model_;
  glm::mat4 view_;
  glm::mat4 proj_;
};