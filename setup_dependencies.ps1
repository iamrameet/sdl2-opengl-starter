# Setup dependencies for SDL2 OpenGL Application
# This script downloads and sets up SDL2 and GLAD

# Print header
Write-Host "========================================" -ForegroundColor Blue
Write-Host "   SDL2 OpenGL Dependencies Setup       " -ForegroundColor Blue
Write-Host "========================================" -ForegroundColor Blue
Write-Host ""

# Create directories
Write-Host "Creating directories..." -ForegroundColor Cyan
$directories = @(
    "external",
    "external/SDL2",
    "external/SDL2/include",
    "external/SDL2/lib",
    "external/SDL2/lib/x64",
    "external/GLAD",
    "external/GLAD/include",
    "external/GLAD/include/glad",
    "external/GLAD/include/KHR",
    "external/GLAD/src"
)

foreach ($dir in $directories) {
    if (-not (Test-Path $dir)) {
        New-Item -Path $dir -ItemType Directory -Force | Out-Null
        Write-Host "  Created $dir" -ForegroundColor Gray
    }
}

# Download SDL2
Write-Host "`nDownloading SDL2..." -ForegroundColor Cyan
$sdl2Url = "https://www.libsdl.org/release/SDL2-devel-2.28.5-VC.zip"
$sdl2ZipPath = "SDL2.zip"

try {
    Invoke-WebRequest -Uri $sdl2Url -OutFile $sdl2ZipPath
    Write-Host "  SDL2 downloaded successfully" -ForegroundColor Green

    # Extract SDL2
    Write-Host "Extracting SDL2..." -ForegroundColor Cyan
    Expand-Archive -Path $sdl2ZipPath -DestinationPath "temp_sdl2" -Force

    # Copy files to the right locations
    Write-Host "Copying SDL2 files..." -ForegroundColor Cyan
    Copy-Item -Path "temp_sdl2/SDL2-2.28.5/include/*" -Destination "external/SDL2/include/" -Recurse -Force
    Copy-Item -Path "temp_sdl2/SDL2-2.28.5/lib/x64/*" -Destination "external/SDL2/lib/x64/" -Force

    # Clean up
    Remove-Item -Path $sdl2ZipPath -Force
    Remove-Item -Path "temp_sdl2" -Recurse -Force

    Write-Host "  SDL2 setup completed" -ForegroundColor Green
} catch {
    Write-Host "  Failed to download or extract SDL2: $_" -ForegroundColor Red
    Write-Host "  Please download SDL2 manually from https://www.libsdl.org/download-2.0.php" -ForegroundColor Yellow
}

# Download GLAD
Write-Host "`nSetting up GLAD..." -ForegroundColor Cyan
Write-Host "GLAD needs to be generated and downloaded manually from https://glad.dav1d.de/" -ForegroundColor Yellow
Write-Host "Please follow these steps:" -ForegroundColor Yellow
Write-Host "1. Go to https://glad.dav1d.de/" -ForegroundColor Yellow
Write-Host "2. Configure with:" -ForegroundColor Yellow
Write-Host "   - Language: C/C++" -ForegroundColor Yellow
Write-Host "   - Specification: OpenGL" -ForegroundColor Yellow
Write-Host "   - API: gl Version 4.0" -ForegroundColor Yellow
Write-Host "   - Profile: Compatibility" -ForegroundColor Yellow
Write-Host "   - Options: Check 'Generate a loader'" -ForegroundColor Yellow
Write-Host "3. Click 'Generate' and download the zip file" -ForegroundColor Yellow
Write-Host "4. Extract the following files to your project:" -ForegroundColor Yellow
Write-Host "   - glad.h → place in external/GLAD/include/glad/" -ForegroundColor Yellow
Write-Host "   - khrplatform.h → place in external/GLAD/include/KHR/" -ForegroundColor Yellow
Write-Host "   - glad.c → place in external/GLAD/src/" -ForegroundColor Yellow

Write-Host "`nDependency setup completed!" -ForegroundColor Green
Write-Host "You can now build the project by running:" -ForegroundColor Green
Write-Host "  .\compile_and_run.ps1" -ForegroundColor Cyan
