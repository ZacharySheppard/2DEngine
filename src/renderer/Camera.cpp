#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height) {
  model_ = glm::mat4(1.0f);

  constexpr glm::vec3 target{0.0f, 0.0f, 0.0f};
  setCameraPosition(target);
  float aspect = static_cast<float>(width) / static_cast<float>(height);
  proj_ = glm::ortho(aspect, -aspect, -1.0f, 1.0f);
}

glm::mat4 OrthographicCamera::mvp() const noexcept { return proj_ * view_ * model_; }

void OrthographicCamera::setCameraPosition(glm::vec3 pos) noexcept {
  constexpr glm::vec3 up{0.0f, 1.0f, 0.0f};
  constexpr glm::vec3 camPos{0.0f, 0.0f, 1.0f};
  view_ = glm::lookAt(camPos, pos, up);
}