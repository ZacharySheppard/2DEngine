#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <algorithm>
OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height) {
  constexpr glm::vec3 target{0.0f, 0.0f, 0.0f};
  constexpr float zoom = 3.0f;
  aspectRatio_ = static_cast<float>(width) / static_cast<float>(height);
  setTarget(target);
  setZoom(zoom);
}

glm::mat4 OrthographicCamera::mvp() const noexcept { return proj_ * view_ * glm::mat4(1.0f); }

float OrthographicCamera::zoom() const noexcept { return zoom_; }

void OrthographicCamera::setZoom(float zoom) noexcept {
  zoom_ = std::max(zoom, 1.0f);
  proj_ = glm::ortho(zoom_ * aspectRatio_, -zoom_ * aspectRatio_, -1.0f * zoom_, zoom_);
}

void OrthographicCamera::setTarget(glm::vec3 pos) noexcept {
  target_ = pos;
  constexpr glm::vec3 up{0.0f, 1.0f, 0.0f};

  view_ = glm::lookAt({target_.x, target_.y, 1.0f}, target_, up);
}

glm::vec3 OrthographicCamera::target() const noexcept { return target_; }

float OrthographicCamera::aspectRatio() const noexcept { return aspectRatio_; }