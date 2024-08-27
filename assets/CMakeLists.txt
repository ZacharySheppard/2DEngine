if (MSVC)
    set(SHADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
    set(TARGET_DIR ${CMAKE_BINARY_DIR}/src/application/${CMAKE_BUILD_TYPE}/assets/shaders)
    configure_file(${SHADER_PATH}/fragment.GLSL ${TARGET_DIR}/fragment.GLSL COPYONLY)
    configure_file(${SHADER_PATH}/vertex.GLSL ${TARGET_DIR}/vertex.GLSL COPYONLY)
endif()

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION .
    FILES_MATCHING PATTERN "*.glsl"
)
