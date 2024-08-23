set(TARGET_NAME renderer)

add_library(${TARGET_NAME})
add_library(2D_ENGINE::${TARGET_NAME} ALIAS ${TARGET_NAME})

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 23)
target_sources(${TARGET_NAME}
    PUBLIC
        Buffers.cpp
        Shader.cpp
        Draw.cpp
        Texture.cpp
        Camera.cpp
)

target_link_libraries(${TARGET_NAME}
    2D_ENGINE::logger
    glfw 
    glad::glad 
    glm::glm    
)

target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)

install(TARGETS ${TARGET_NAME}
DESTINATION .
)
