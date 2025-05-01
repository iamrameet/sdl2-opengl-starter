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
    if (Test-Path "build\obj") {
        Remove-Item "build\obj\*" -Force -Recurse
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

    # Create obj directory if it doesn't exist
    if (-not (Test-Path "build\obj")) {
        New-Item -Path "build\obj" -ItemType Directory -Force | Out-Null
    }

    # Compile the program
    Write-Host "Compiling the program..." -ForegroundColor Green
    & cl /EHsc /W4 /I"engine\include" /I"game\include" /I"third_party\SDL2\include" /I"third_party\GLAD\include" /I"third_party\GLM\include" /Fo"build\obj\\" game\src\main.cpp engine\src\Application.cpp engine\src\GameObject.cpp engine\src\Shader.cpp engine\src\Renderer.cpp engine\src\UISystem.cpp game\src\TopDownShooterGame.cpp game\src\Player.cpp game\src\Enemy.cpp game\src\Projectile.cpp game\src\Level.cpp third_party\GLAD\src\glad.c /Fe:bin\gameClient.exe /link "third_party\SDL2\lib\x64\SDL2.lib" "third_party\SDL2\lib\x64\SDL2main.lib" opengl32.lib Shell32.lib /SUBSYSTEM:CONSOLE

    # Check if compilation was successful
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Compilation successful!" -ForegroundColor Green

        # Copy SDL2.dll to bin directory
        Write-Host "Copying SDL2.dll to bin directory..." -ForegroundColor Cyan
        Copy-Item "third_party\SDL2\lib\x64\SDL2.dll" "bin\" -Force

        # Create shader directory and copy shader files
        Write-Host "Copying shader files..." -ForegroundColor Cyan
        if (-not (Test-Path "bin\shaders")) {
            New-Item -Path "bin\shaders" -ItemType Directory -Force | Out-Null
        }
        Copy-Item "shaders\basic.vert" "bin\shaders\" -Force
        Copy-Item "shaders\basic.frag" "bin\shaders\" -Force
    } else {
        Write-Host "Compilation failed!" -ForegroundColor Red
        exit 1
    }
}

# Skip running if CompileOnly is specified
if (-not $CompileOnly) {
    # Check if executable exists
    if (-not (Test-Path "bin\gameClient.exe")) {
        Write-Host "Executable not found. Please compile the program first." -ForegroundColor Red
        exit 1
    }

    # Run the program
    Write-Host "\nRunning the program:" -ForegroundColor Green
    Write-Host "----------------------------------------" -ForegroundColor DarkGray
    & "bin\gameClient.exe"
    Write-Host "----------------------------------------" -ForegroundColor DarkGray

    # Check exit code
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Program executed successfully." -ForegroundColor Green
    } else {
        Write-Host "Program exited with code $LASTEXITCODE" -ForegroundColor Yellow
    }
}

Write-Host "\nDone!" -ForegroundColor Blue
