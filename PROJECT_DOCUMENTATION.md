# SDL2 OpenGL Project Documentation

## Project Overview

This project is a cross-platform 2D application using SDL2 and OpenGL with GLAD. It demonstrates how to set up a basic OpenGL rendering pipeline with shaders in C++, with the goal of creating a 2D multiplayer game with voice chat support.

## Key Technologies

- **SDL2**: Used for window creation, input handling, and OpenGL context setup
- **OpenGL 4.0**: Modern OpenGL with programmable pipeline
- **GLAD**: OpenGL loader library (preferred over GLEW for modern OpenGL)
- **GLSL Shaders**: Used for rendering with the programmable pipeline
- **ENet**: Planned for networking and multiplayer functionality
- **OpenAL** or **SDL_mixer**: Planned for audio and voice chat implementation

## Project Structure

```
.
├── assets/            # Asset files
│   └── shaders/       # GLSL shader files
│       ├── basic.frag # Fragment shader
│       └── basic.vert # Vertex shader
├── bin/               # Compiled binaries
│   └── .gitkeep       # Placeholder to keep directory in git
├── external/          # External dependencies (not in git)
│   ├── GLAD/          # OpenGL loader
│   ├── GLM/           # OpenGL Mathematics library
│   └── SDL2/          # Simple DirectMedia Layer
├── include/           # Header files
│   ├── Core/          # Core game components
│   ├── GameObjects/   # Game object implementations
│   ├── Graphics/      # Rendering components
│   └── UI/            # User interface components
├── lib/               # Library files
│   └── .gitkeep       # Placeholder to keep directory in git
├── src/               # Source code
│   ├── Core/          # Core game components
│   ├── GameObjects/   # Game object implementations
│   ├── Graphics/      # Rendering components
│   ├── UI/            # User interface components
│   └── main.cpp       # Main application code
├── .git/              # Git repository data
│   └── config         # Git configuration (using rameet_personal SSH key)
├── .gitignore         # Git ignore rules
├── CMakeLists.txt     # CMake build configuration (alternative)
├── compile_and_run.ps1 # PowerShell build script (primary build method)
├── PROJECT_DOCUMENTATION.md # This file
├── README.md          # User-facing documentation
└── setup_dependencies.ps1 # Script to download and set up dependencies
```

## Build System

The project has been simplified to use a single primary build method with an alternative option:

1. **PowerShell Script** (`compile_and_run.ps1`):
   - Primary build method
   - Supports compile-only, run-only, and clean modes
   - Automatically sets up Visual Studio environment
   - Handles all asset copying and dependency management

2. **CMake** (`CMakeLists.txt`):
   - Alternative cross-platform build system
   - Available as a fallback option
   - Useful for IDE integration

## Dependencies Management

External dependencies are not included in the Git repository. Instead:

1. A setup script (`setup_dependencies.ps1`) helps download and set up SDL2
2. The README includes instructions for manually setting up GLAD
3. The `.gitignore` file excludes the `external/` directory

## Git Configuration

The repository is configured to use a specific SSH key:

```
[core]
    sshCommand = ssh -i ~/.ssh/rameet_personal
```

This ensures that Git operations use the specified SSH key instead of the default one.

## Current Implementation

The current implementation:

1. Creates a window using SDL2
2. Sets up an OpenGL 4.0 context
3. Initializes GLAD to load OpenGL functions
4. Compiles and links vertex and fragment shaders
5. Creates a 2D triangle with vertex colors
6. Implements simple 2D animation (rotation and scaling)
7. Handles basic input (ESC to exit)

This serves as the foundation for a 2D vector-based game, where all game objects will be rendered using OpenGL primitives or textures.

## Rendering Pipeline

The rendering pipeline follows modern OpenGL practices:

1. Vertex data is stored in Vertex Buffer Objects (VBOs)
2. Vertex Array Objects (VAOs) store vertex attribute configurations
3. GLSL shaders handle vertex transformation and fragment coloring
4. A simple matrix class handles transformations

## Planned Networking Architecture

The multiplayer functionality will be implemented using ENet:

1. **Client-Server Model**: A dedicated server will manage game state
2. **State Synchronization**: Server will broadcast authoritative game state
3. **Input Prediction**: Clients will predict movement to reduce perceived latency
4. **Packet Reliability**: ENet provides reliable and unreliable packet delivery

## Planned Voice Chat System

The voice chat system will use the following components:

1. **Audio Capture**: Record audio from the user's microphone
2. **Compression**: Compress audio data using a codec like Opus
3. **Transmission**: Send compressed audio data over the network
4. **Playback**: Decompress and play received audio from other players
5. **Mixing**: Mix audio streams from multiple players

## Future Plans

Potential enhancements for the future:

1. **2D Multiplayer**: Implement network-based multiplayer functionality
   - Client-server architecture
   - Player synchronization
   - Game state management
2. **Voice Chat**: Add real-time voice communication
   - Audio capture and playback
   - Voice data compression
   - Network transmission of voice data
3. **Texture Support**: Add texture loading and rendering
4. **2D Physics**: Implement collision detection and response
5. **Input Handling**: More comprehensive input handling
6. **Audio**: Add audio support using SDL_mixer
7. **UI System**: Simple UI rendering for game menus and HUD
8. **Resource Management**: Better resource loading and management
9. **Cross-Platform Testing**: Ensure it works on Windows, macOS, and Linux

## Development Decisions

Key decisions made during development:

1. **GLAD over GLEW**: Chose GLAD as it's more modern and flexible
2. **OpenGL 4.0**: Provides a good balance of features and compatibility
3. **Compatibility Profile**: Allows access to both modern and legacy OpenGL functions
4. **No External Dependencies in Git**: Keeps repository size small and avoids licensing issues
5. **Simplified Build System**: Single primary build method (PowerShell) with CMake as alternative
6. **Custom SSH Key**: Uses a specific SSH key for Git operations

## GitHub Repository

The project is hosted on GitHub:
- Repository: https://github.com/iamrameet/sdl2-opengl-starter
- Owner: iamrameet

## Notes on Git Authentication

There appears to be a mismatch between the GitHub account "iamrameet" and the authenticated account "rameet-mashta". Options to resolve this:

1. Add "rameet-mashta" as a collaborator to the "iamrameet" repository
2. Use a personal access token for authentication
3. Change the repository owner to match the authenticated account
4. Use SSH with the correct GitHub account

## License

The project is open source and available under the MIT License.
