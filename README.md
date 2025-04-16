# SDL2 OpenGL Application

A simple cross-platform application using SDL2 and OpenGL with GLAD. This project demonstrates how to set up a basic OpenGL rendering pipeline with shaders in C++.

## Features

- SDL2 for window creation and event handling
- Modern OpenGL (4.0) with GLAD loader
- GLSL shaders for rendering
- Simple matrix math for transformations
- Animated triangle with color interpolation

## Project Structure

```
.
├── assets/            # Asset files
│   └── shaders/       # GLSL shader files
├── bin/               # Compiled binaries
├── external/          # External dependencies
│   ├── GLAD/          # OpenGL loader
│   └── SDL2/          # Simple DirectMedia Layer
├── lib/               # Library files
├── src/               # Source code
│   └── main.cpp       # Main application code
├── build.bat          # Build script using CMake
├── CMakeLists.txt     # CMake build configuration
├── compile_and_run.ps1 # PowerShell build script
├── compile_and_run_vs.bat # Batch file for Visual Studio compilation
└── README.md          # This file
```

## Building and Running

### Using PowerShell (Recommended)

```powershell
# Build and run
.\compile_and_run.ps1

# Build only
.\compile_and_run.ps1 -CompileOnly

# Run only
.\compile_and_run.ps1 -RunOnly

# Clean build artifacts
.\compile_and_run.ps1 -Clean
```

### Using Visual Studio Batch File

```batch
compile_and_run_vs.bat
```

### Using CMake

1. Run the build script:
   ```
   build.bat
   ```

Or manually:

```bash
# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the program
cmake --build . --config Release

# Run the program
.\bin\Release\sdl_app.exe
```

### Manual Compilation with Visual C++

```bash
# In the Developer Command Prompt
cl /EHsc /I"external\SDL2\include" /I"external\GLAD\include" src\main.cpp external\GLAD\src\glad.c /Fe:bin\sdl_app.exe /link "external\SDL2\lib\x64\SDL2.lib" "external\SDL2\lib\x64\SDL2main.lib" opengl32.lib Shell32.lib /SUBSYSTEM:CONSOLE

# Copy SDL2.dll to bin directory
copy "external\SDL2\lib\x64\SDL2.dll" "bin\"

# Create shader directory
mkdir "bin\assets\shaders"

# Copy shader files
copy "assets\shaders\basic.vert" "bin\assets\shaders\"
copy "assets\shaders\basic.frag" "bin\assets\shaders\"

# Run the program
bin\sdl_app.exe
```

## Controls

- **ESC**: Exit the application
- **Close Window Button**: Exit the application

## Requirements

- Windows with Visual Studio 2022 (Community or Build Tools)
- C++17 compatible compiler
- SDL2 (needs to be downloaded separately)
- GLAD (needs to be downloaded separately)
- Optional: CMake 3.10+ for using the CMake build system
- Optional: PowerShell 5.1+ for using the PowerShell build script

## Setting Up Dependencies

This project requires SDL2 and GLAD, which are not included in the repository. Follow these steps to set them up:

### Setting up SDL2

1. Download SDL2 development libraries for Windows from [SDL's website](https://www.libsdl.org/download-2.0.php)
2. Extract the contents to `external/SDL2/`
3. Ensure the following directory structure:
   ```
   external/SDL2/
   ├── include/     # Header files
   └── lib/
       └── x64/    # 64-bit libraries
           ├── SDL2.dll
           ├── SDL2.lib
           └── SDL2main.lib
   ```

### Setting up GLAD

1. Go to the [GLAD web service](https://glad.dav1d.de/)
2. Configure with:
   - Language: C/C++
   - Specification: OpenGL
   - API: gl Version 4.0
   - Profile: Compatibility
   - Options: Check "Generate a loader"
3. Click "Generate" and download the zip file
4. Extract the following files to your project:
   - `glad.h` → place in `external/GLAD/include/glad/`
   - `khrplatform.h` → place in `external/GLAD/include/KHR/`
   - `glad.c` → place in `external/GLAD/src/`

## License

This project is open source and available under the MIT License.
