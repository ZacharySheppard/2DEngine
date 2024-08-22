#include "Application.hpp"

#include <memory>
#include <vector>

#include "ConfigurationPanel.hpp"
#include "Panel.hpp"
#include "RenderPanel.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "logger/Logger.hpp"
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

  auto originV1 = render.vertices[0].pos;
  auto originV2 = render.vertices[1].pos;
  auto originV3 = render.vertices[2].pos;
  auto originV4 = render.vertices[3].pos;

  while (!window_.shouldClose()) {
    window_.pollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    config.update();

    render.vertices[0].col = glm::vec3{config.ColorV1.x, config.ColorV1.y, config.ColorV1.z};
    render.vertices[1].col = glm::vec3{config.ColorV2.x, config.ColorV2.y, config.ColorV2.z};
    render.vertices[2].col = glm::vec3{config.ColorV3.x, config.ColorV3.y, config.ColorV3.z};
    render.vertices[0].pos = glm::vec2{originV1.x + config.Offset.x, originV1.y + config.Offset.y};
    render.vertices[1].pos = glm::vec2{originV2.x + config.Offset.x, originV2.y + config.Offset.y};
    render.vertices[2].pos = glm::vec2{originV3.x + config.Offset.x, originV3.y + config.Offset.y};
    render.vertices[3].pos = glm::vec2{originV4.x + config.Offset.x, originV4.y + config.Offset.y};
    render.bgColor = {config.ColorBG.x, config.ColorBG.y, config.ColorBG.z};
    render.update();
    // render frames
    ImGui::Render();
    auto [width, height] = window_.getFrameBufferSize();
    resizeUI(config, render, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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