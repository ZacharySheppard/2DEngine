set(APPLICATION_NAME 2D_ENGINE)

set(TARGET_SOURCES
    main.cpp
    Window.cpp
    Logger.cpp
    Application.cpp
    ConfigurationPanel.cpp
    RenderPanel.cpp
)

add_executable(${APPLICATION_NAME} ${TARGET_SOURCES})
set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD 23)

target_link_libraries(${APPLICATION_NAME}
    glfw 
    glad::glad 
    glm::glm
    spdlog::spdlog 
    imgui::imgui
)

install(TARGETS ${APPLICATION_NAME}
DESTINATION .
)
