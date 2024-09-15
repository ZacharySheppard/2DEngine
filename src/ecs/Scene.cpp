#include "Scene.hpp"

Entity Scene::createEntity() noexcept {
  const auto entity = registry_.create();
  return Entity{static_cast<uint64_t>(entity)};
}