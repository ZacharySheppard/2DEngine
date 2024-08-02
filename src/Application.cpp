#include "Application.hpp"

#include "Layout.hpp"
#include "Logger.hpp"
#include "Panel.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
Application::Application(Window window) : window_(std::move(window)) {}

bool Application::run() const noexcept {
  // Setup Dear ImGui context
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
  auto dummy = DummyPanel("Hello Riley");
  auto dummy2 = DummyPanel("Hello Jasper");
  auto dummy3 = DummyPanel("Hello Zach");
  dummy.resize({400, 200});
  dummy2.resize({200, 200});
  dummy3.resize({400, 200});
  auto layout = VerticalLayout();
  layout.addPanel(dummy);
  layout.addPanel(dummy2);
  layout.addPanel(dummy3);
  while (!window_.shouldClose()) {
    window_.pollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    dummy3.update();
    dummy.update();
    dummy2.update();
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window_.window(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window_.swapBuffers();
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return true;
}