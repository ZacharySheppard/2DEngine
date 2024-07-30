#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
class Window {
 public:
  Window(uint32_t width, uint32_t height, std::string name) noexcept;
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&);
  Window& operator=(Window&&);

  bool shouldClose() const noexcept;
  void swapBuffers() const noexcept;
  void pollEvents() const noexcept;  

  GLFWwindow* window() const noexcept;

 private:
  GLFWwindow* window_;
};
