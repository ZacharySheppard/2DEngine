#include "Application.hpp"

#include <memory>
#include <vector>

#include "Logger.hpp"
#include "Panel.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace {
void resizeUI(ConfigurationPanel& cfg, OpenGLRenderPanel& rnd, float w, float h) {
  const auto sidebarSize = Size{0.2f * w, h};
  cfg.resize(sidebarSize);
  const auto renderSize = Size{0.8f * w, h};
  const auto renderPos = Point{0.2f * w, 0.f};
  rnd.resize(renderSize);
  rnd.move(renderPos);
}
}  // namespace

Application::Application(Window window) : window_(std::move(window)) {}

bool Application::run() const noexcept {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    logger::info("failed to create an opengl context");
    return false;
  }
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  ImGui_ImplGlfw_InitForOpenGL(window_.window(), true);
  ImGui_ImplOpenGL3_Init();
  auto [initialWidth, initialHeight] = window_.getFrameBufferSize();
  auto config = ConfigurationPanel("configuration", Size{initialWidth * 0.2f, initialHeight});
  auto render = OpenGLRenderPanel("render", Size{initialWidth * 0.8f, initialHeight}, Point{initialWidth * 0.2f, 0});

  while (!window_.shouldClose()) {
    window_.pollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    config.update();
    render.update();
    // render frames
    ImGui::Render();
    auto [width, height] = window_.getFrameBufferSize();
    resizeUI(config, render, width, height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window_.swapBuffers();
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return true;
}