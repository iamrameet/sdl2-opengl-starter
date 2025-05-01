# Third-party libraries

# GLM (header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/GLM/include")

# GLAD (OpenGL loader)
add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/GLAD/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLAD/include")

# SDL2
if(WIN32)
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include")
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib" "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2main.lib")
    set(SDL2_DLL "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll")
    
    add_library(SDL2 INTERFACE)
    target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES})
else()
    find_package(SDL2 REQUIRED)
    add_library(SDL2 INTERFACE)
    target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
add_library(opengl INTERFACE)
target_link_libraries(opengl INTERFACE ${OPENGL_LIBRARIES})
