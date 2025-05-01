# Game client

# Define the game client executable
add_executable(gameClient
    src/main.cpp
    src/TopDownShooterGame.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Projectile.cpp
    src/Level.cpp
)

# Include directories
target_include_directories(gameClient
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link with dependencies
target_link_libraries(gameClient
    PRIVATE
        engine
)

# Windows-specific settings
if(WIN32)
    # Set the subsystem to Windows for GUI applications
    set_target_properties(gameClient PROPERTIES
        WIN32_EXECUTABLE TRUE
    )

    # Copy SDL2.dll to output directory
    add_custom_command(TARGET gameClient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_DLL}
        $<TARGET_FILE_DIR:gameClient>
    )
endif()
