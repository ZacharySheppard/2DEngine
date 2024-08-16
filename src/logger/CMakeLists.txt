set(TARGET_NAME logger)

add_library(${TARGET_NAME})
add_library(2D_ENGINE::${TARGET_NAME} ALIAS ${TARGET_NAME})
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 23)
target_sources(${TARGET_NAME}
    PUBLIC
        Logger.cpp
)

target_link_libraries(${TARGET_NAME}
    spdlog::spdlog 
)

install(TARGETS ${APPLICATION_NAME}
DESTINATION .
)
