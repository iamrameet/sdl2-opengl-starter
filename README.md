# 2D Multiplayer Game

A cross-platform 2D vector-based multiplayer game built with C++, Modern OpenGL, SDL2, and ENet.

## Features

- SDL2 for window creation and event handling
- Modern OpenGL (4.0) with GLAD loader
- GLSL shaders for rendering
- Vector-based graphics with GLM for mathematics
- Client-server architecture for multiplayer
- Voice chat support (planned)

## Project Structure

```
./
├── CMakeLists.txt            # Root CMake configuration
├── CMakeModules/             # Custom CMake find scripts
├── assets/                   # Game assets: images, sounds, maps
├── shaders/                  # GLSL shaders (vertex/fragment)
├── engine/                   # Core engine modules (rendering, input, networking)
│   ├── include/              # Engine header files
│   ├── src/                  # Engine source files
│   └── CMakeLists.txt        # Engine build configuration
├── game/                     # Game-specific client logic
│   ├── include/              # Game header files
│   ├── src/                  # Game source files
│   └── CMakeLists.txt        # Game build configuration
├── server/                   # Dedicated multiplayer server code
│   ├── include/              # Server header files
│   ├── src/                  # Server source files
│   └── CMakeLists.txt        # Server build configuration
├── third_party/              # External dependencies
│   ├── SDL2/                 # Simple DirectMedia Layer
│   ├── GLAD/                 # OpenGL loader
│   └── GLM/                  # OpenGL Mathematics
├── docs/                     # Design docs and notes
├── tests/                    # Unit tests
├── tools/                    # Editors, map tools, etc.
├── compile_and_run.ps1       # PowerShell build script (primary build method)
└── README.md                 # This file
```

## Building and Running

### Using CMake (Recommended)

```bash
# Create a build directory
mkdir -p build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release

# Run the game client
./bin/gameClient

# Run the dedicated server (when implemented)
./bin/gameServer
```

### Windows Build with PowerShell

This project also includes a PowerShell script for building and running on Windows. The script automatically sets up the Visual Studio environment, compiles the code, and handles asset copying.

```powershell
# Build and run (default)
.\compile_and_run.ps1

# Build only
.\compile_and_run.ps1 -CompileOnly

# Run only
.\compile_and_run.ps1 -RunOnly

# Clean build artifacts
.\compile_and_run.ps1 -Clean
```

## Controls

- **WASD/Arrow Keys**: Move the player
- **Space/Left Mouse Button**: Shoot
- **ESC**: Exit the application
- **Close Window Button**: Exit the application

## Requirements

- C++17 compatible compiler
- CMake 3.10 or higher
- Windows, Linux, or macOS
- For Windows: Visual Studio 2022 (Community or Build Tools)
- For PowerShell script: PowerShell 5.1+

## Dependencies

All dependencies are included in the `third_party` directory:

- **SDL2**: Window creation and input handling
- **GLAD**: OpenGL function loader
- **GLM**: OpenGL Mathematics library for vector/matrix operations

## Project Components

### Engine

The engine provides core functionality that can be reused across different games:

- Rendering system with OpenGL
- Input handling with SDL2
- Audio system
- Networking for multiplayer
- Entity-Component System (ECS)

### Game

The game layer implements the specific game logic:

- Player controls and movement
- Enemy AI
- Projectile physics
- Game states (menu, play, pause)
- UI elements

### Server

The server component handles the multiplayer aspects:

- Game state synchronization
- Client connections
- Voice chat relay
- Game logic validation

## License

This project is open source and available under the MIT License.
