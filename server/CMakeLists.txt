# Game server

# Define the game server executable
add_executable(gameServer
    src/main.cpp
)

# Include directories
target_include_directories(gameServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link with dependencies
target_link_libraries(gameServer
    PRIVATE
        engine
)
