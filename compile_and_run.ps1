# Compile and run the SDL2 OpenGL application using PowerShell

# Define parameters
param (
    [switch]$CompileOnly,
    [switch]$RunOnly,
    [switch]$Clean
)

# Print header
Write-Host "========================================" -ForegroundColor Blue
Write-Host "   SDL2 OpenGL Application Builder    " -ForegroundColor Blue
Write-Host "========================================" -ForegroundColor Blue
Write-Host ""

# Clean build if requested
if ($Clean) {
    Write-Host "Cleaning build artifacts..." -ForegroundColor Yellow
    if (Test-Path "bin\sdl_app.exe") {
        Remove-Item "bin\sdl_app.exe" -Force
    }
    if (Test-Path "*.obj") {
        Remove-Item "*.obj" -Force
    }
    Write-Host "Clean completed." -ForegroundColor Green
    if (-not ($CompileOnly -or $RunOnly)) {
        exit 0
    }
}

# Skip compilation if RunOnly is specified
if (-not $RunOnly) {
    # Set up Visual Studio environment
    $vsPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    if (-not (Test-Path $vsPath)) {
        $vsPath = "C:\Program Files (x86)\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    }
    if (-not (Test-Path $vsPath)) {
        $vsPath = "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    }
    if (-not (Test-Path $vsPath)) {
        $vsPath = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    }

    if (Test-Path $vsPath) {
        Write-Host "Setting up Visual Studio environment..." -ForegroundColor Cyan
        & cmd /c "`"$vsPath`" && set" | ForEach-Object {
            if ($_ -match "^([^=]+)=(.*)$") {
                [System.Environment]::SetEnvironmentVariable($matches[1], $matches[2])
            }
        }
    } else {
        Write-Host "Visual Studio environment not found. Please install Visual Studio 2022 with C++ development tools." -ForegroundColor Red
        exit 1
    }

    # Compile the program
    Write-Host "Compiling the program..." -ForegroundColor Green
    & cl /EHsc /W4 /I"external\SDL2\include" /I"external\GLAD\include" src\main.cpp external\GLAD\src\glad.c /Fe:bin\sdl_app.exe /link "external\SDL2\lib\x64\SDL2.lib" "external\SDL2\lib\x64\SDL2main.lib" opengl32.lib Shell32.lib /SUBSYSTEM:CONSOLE

    # Check if compilation was successful
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Compilation successful!" -ForegroundColor Green

        # Copy SDL2.dll to bin directory
        Write-Host "Copying SDL2.dll to bin directory..." -ForegroundColor Cyan
        Copy-Item "external\SDL2\lib\x64\SDL2.dll" "bin\" -Force

        # Create shader directory and copy shader files
        Write-Host "Copying shader files..." -ForegroundColor Cyan
        if (-not (Test-Path "bin\assets\shaders")) {
            New-Item -Path "bin\assets\shaders" -ItemType Directory -Force | Out-Null
        }
        Copy-Item "assets\shaders\basic.vert" "bin\assets\shaders\" -Force
        Copy-Item "assets\shaders\basic.frag" "bin\assets\shaders\" -Force
    } else {
        Write-Host "Compilation failed!" -ForegroundColor Red
        exit 1
    }
}

# Skip running if CompileOnly is specified
if (-not $CompileOnly) {
    # Check if executable exists
    if (-not (Test-Path "bin\sdl_app.exe")) {
        Write-Host "Executable not found. Please compile the program first." -ForegroundColor Red
        exit 1
    }

    # Run the program
    Write-Host "\nRunning the program:" -ForegroundColor Green
    Write-Host "----------------------------------------" -ForegroundColor DarkGray
    & "bin\sdl_app.exe"
    Write-Host "----------------------------------------" -ForegroundColor DarkGray

    # Check exit code
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Program executed successfully." -ForegroundColor Green
    } else {
        Write-Host "Program exited with code $LASTEXITCODE" -ForegroundColor Yellow
    }
}

Write-Host "\nDone!" -ForegroundColor Blue
