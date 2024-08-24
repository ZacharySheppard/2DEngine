#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height) {
  constexpr glm::vec3 target{0.0f, 0.0f, 0.0f};
  setCameraPosition(target);
  float aspect = static_cast<float>(width) / static_cast<float>(height);
  proj_ = glm::ortho(aspect, -aspect, -1.0f, 1.0f);
}

glm::mat4 OrthographicCamera::mvp() const noexcept { return proj_ * view_ * glm::mat4(1.0f); }

void OrthographicCamera::setCameraPosition(glm::vec3 pos) noexcept {
  target_ = pos;
  constexpr glm::vec3 up{0.0f, 1.0f, 0.0f};

  view_ = glm::lookAt({target_.x, target_.y, 1.0f}, target_, up);
}

glm::vec3 OrthographicCamera::getCameraTarget() const noexcept { return target_; }