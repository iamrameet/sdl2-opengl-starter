@echo off
echo Building SDL2 Application with CMake...

:: Check for CMake
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo CMake not found!
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

:: Create build directory if it doesn't exist
if not exist build mkdir build

:: Navigate to build directory
cd build

:: Generate build files
echo Generating build files with CMake...
cmake .. -G "Visual Studio 17 2022" -A x64

:: Build the project
echo Building the project...
cmake --build . --config Release

:: Check if build was successful
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo The executable is located at: build\bin\Release\sdl_app.exe
    echo.
    echo Running the program:
    echo.
    bin\Release\sdl_app.exe
) else (
    echo.
    echo Build failed!
)

:: Return to the original directory
cd ..

pause
