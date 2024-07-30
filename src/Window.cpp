#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <format>
#include <utility>

namespace {

void errorCallback(int i, const char* message) {
  const auto error = std::format("[Error {}]\n\t{}", i, message);
  spdlog::info(error);
}
}  // namespace
Window::Window(uint32_t width, uint32_t height, std::string name) noexcept : window_(nullptr) {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

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
  if (window_) {
    glfwDestroyWindow(window_);
  }
}

Window::Window(Window&& other) : window_(other.window_) { other.window_ = nullptr; }

Window& Window::operator=(Window&& other) {
  window_ = other.window_;
  other.window_ = nullptr;
  return *this;
}

bool Window::shouldClose() const noexcept { return glfwWindowShouldClose(window_); }
void Window::swapBuffers() const noexcept { glfwSwapBuffers(window_); }
void Window::pollEvents() const noexcept { glfwPollEvents(); }

GLFWwindow* Window::window() const noexcept { return window_; }
