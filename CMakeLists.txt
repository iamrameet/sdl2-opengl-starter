cmake_minimum_required(VERSION 3.10)
project(SDLApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# SDL2 configuration
if(WIN32)
    set(SDL2_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/SDL2/include")
    set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.lib" "${CMAKE_SOURCE_DIR}/external/SDL2/lib/x64/SDL2main.lib")
    set(SDL2_DLL "${CMAKE_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.dll")
else()
    find_package(SDL2 REQUIRED)
endif()

# OpenGL configuration
find_package(OpenGL REQUIRED)

# GLAD configuration
set(GLAD_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/GLAD/include")
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/external/GLAD/src/glad.c")
target_include_directories(glad PRIVATE ${GLAD_INCLUDE_DIRS})

# Set GLM include directory
set(GLM_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/external/GLM/include")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
)

# Add executable
add_executable(sdl_app
    src/main.cpp
    src/Core/Game.cpp
    src/Core/GameObject.cpp
    src/GameObjects/Triangle.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Shader.cpp
    src/UI/UISystem.cpp
)

# Link libraries
if(WIN32)
    target_link_libraries(sdl_app
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        glad
        Shell32
    )
else()
    target_link_libraries(sdl_app
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        glad
    )
endif()

# Windows-specific settings
if(WIN32)
    # Set the subsystem to Windows for GUI applications
    set_target_properties(sdl_app PROPERTIES
        WIN32_EXECUTABLE TRUE
    )

    # Copy SDL2.dll to output directory
    add_custom_command(TARGET sdl_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_DLL}
        $<TARGET_FILE_DIR:sdl_app>
    )

    # Copy shader files to output directory
    add_custom_command(TARGET sdl_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:sdl_app>/assets/shaders
    )

    add_custom_command(TARGET sdl_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/assets/shaders/basic.vert
        ${CMAKE_SOURCE_DIR}/assets/shaders/basic.frag
        $<TARGET_FILE_DIR:sdl_app>/assets/shaders/
    )
endif()
