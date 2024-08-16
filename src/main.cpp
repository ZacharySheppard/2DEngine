#include "Application.hpp"
#include "logger/Logger.hpp"
auto main() -> int {
  const auto couldInitialize = logger::initialize();
  if (!couldInitialize) {
    return 1;
  }
  logger::info("Starting Application");
  auto surface = Window(1920, 1080, "2D Engine");
  auto app = Application(std::move(surface));
  auto wasRunSuccessful = app.run();
  if (!wasRunSuccessful) {
    logger::info("Application Crash");
  }
}
