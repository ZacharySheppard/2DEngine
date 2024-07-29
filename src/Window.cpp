#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <format>
#include <utility>

namespace {

void errorCallback(int i, const char* message) {
  const auto error = std::format("Got Error {}\nWith message: {}", i, message);
  spdlog::info(error);
}
}  // namespace
Window::Window(uint32_t width, uint32_t height, std::string name) noexcept {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window_ = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (!window_) {
    glfwTerminate();
    exit(1);
  }

  // glfwSetKeyCallback(window, key_callback);
  //
  glfwMakeContextCurrent(window_);
  glfwSwapInterval(0);
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

bool Window::shouldClose() const noexcept { return glfwWindowShouldClose(window_); }
void Window::swapBuffers() const noexcept { glfwSwapBuffers(window_); }
void Window::pollEvents() const noexcept { glfwPollEvents(); }

Window::Window(Window&& other) { std::exchange(window_, other.window_); }

Window& Window::operator=(Window&& other) {
  std::exchange(this->window_, other.window_);
  return *this;
}
