# Engine library

# Define the engine library
add_library(engine STATIC
    src/Application.cpp
    src/GameObject.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/UISystem.cpp
)

# Include directories
target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link with dependencies
target_link_libraries(engine
    PUBLIC
        SDL2
        glad
        glm
        opengl
)

# Windows-specific settings
if(WIN32)
    target_link_libraries(engine PUBLIC Shell32)
endif()
