
#include "Panel.hpp"
#include "ecs/Scene.hpp"
class ScenePanel : public Panel {
 public:
  ScenePanel(std::string name, Size size, Point position) noexcept;
  void move(Point topleft) noexcept override;
  void resize(Size size) noexcept override;
  [[nodiscard]] Size size() const noexcept override;
  [[nodiscard]] Point position() const noexcept override;
  void update() noexcept override;

 private:
  std::string name_;
  Point position_;
  Size size_;
  Scene scene_;
};