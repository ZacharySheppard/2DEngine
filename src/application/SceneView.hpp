
#include "Panel.hpp"
#include "ecs/Scene.hpp"

class SceneView {
 public:
  SceneView(Panel display) noexcept;
  void update() noexcept;
  Panel& display() noexcept;

 private:
  Panel panel_;
  Scene scene_;
};