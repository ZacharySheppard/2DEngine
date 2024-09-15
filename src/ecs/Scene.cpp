#include "Scene.hpp"

Entity Scene::createEntity() noexcept {
  const auto id = static_cast<uint64_t>(registry_.create());
  const auto transform = TransformComponent{};
  const auto entity = Entity{id};
  addComponent(entity, transform);
  return entity;
}
