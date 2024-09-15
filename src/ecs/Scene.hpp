#pragma once
#include "Transform.hpp"
#include "entt/entt.hpp"

struct Entity {
  uint64_t id;
};

class Scene {
 public:
  [[nodsicard]] Entity createEntity() noexcept;

  template <typename T>
  void addComponent(Entity e, T component) {
    registry_.emplace<T>(static_cast<entt::entity>(e.id), component));
  }

 private:
  entt::registry registry_;
};
