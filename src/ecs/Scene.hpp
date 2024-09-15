#pragma once
#include "Transform.hpp"
#include "entt/entt.hpp"

struct Entity {
  uint64_t id;
};

class Scene {
 public:
  [[nodsicard]] Entity createEntity() noexcept;

 private:
  entt::registry registry_;
};
