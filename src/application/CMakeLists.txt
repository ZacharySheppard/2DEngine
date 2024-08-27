set(TARGET_NAME application)
add_executable(${TARGET_NAME})
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 23)
target_sources(${TARGET_NAME}
    PUBLIC   
    Window.cpp
    Application.cpp
    ConfigurationPanel.cpp
    RenderPanel.cpp
    ScenePanel.cpp
    main.cpp
)


target_link_libraries(${TARGET_NAME}
    2D_ENGINE::logger
    2D_ENGINE::renderer
    2D_ENGINE::ecs
    glfw 
    glad::glad 
    glm::glm    
    imgui::imgui
)

target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)

install(TARGETS ${TARGET_NAME}
DESTINATION .
)

