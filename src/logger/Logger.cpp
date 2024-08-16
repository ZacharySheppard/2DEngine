#include "Logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
namespace logger {

constexpr const char* consoleLoggerTag = "console";
constexpr const char* errorLoggerTag = "error";

bool initialize() noexcept {
  const auto console = spdlog::stdout_color_mt(consoleLoggerTag);
  if (console == nullptr) {
    return false;
  }
  const auto error = spdlog::stderr_color_mt(errorLoggerTag);
  if (error == nullptr) {
    return false;
  }

  return true;
}

bool info(std::string_view message) noexcept {
  auto console = spdlog::get(consoleLoggerTag);
  if (console == nullptr) {
    return false;
  }
  console->info(message);
  return true;
};

bool error(std::string_view message) noexcept {
  auto error = spdlog::get(errorLoggerTag);
  if (error == nullptr) {
    return false;
  }
  error->info(message);
  return true;
}

}  // namespace logger