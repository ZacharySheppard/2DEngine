#include "Logger.hpp"
#include "Window.hpp"
auto main() -> int {
  const auto couldInitialize = logger::initialize();
  if (!couldInitialize) {
    return 1;
  }
  logger::info("Starting Application");
  auto surface = Window(1920, 1080, "2D Engine");

  while (!surface.shouldClose()) {
    surface.pollEvents();
    surface.swapBuffers();
  }
}
