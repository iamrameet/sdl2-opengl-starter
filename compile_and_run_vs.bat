@echo off
echo Compiling and running SDL2 Application with Visual Studio Build Tools...

:: Initialize Visual Studio environment for x64
IF EXIST "C:\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
) ELSE (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
)

:: Compile the program
cl /EHsc /I"external\SDL2\include" /I"external\GLAD\include" src\main.cpp external\GLAD\src\glad.c /Fe:bin\sdl_app.exe /link "external\SDL2\lib\x64\SDL2.lib" "external\SDL2\lib\x64\SDL2main.lib" opengl32.lib Shell32.lib /SUBSYSTEM:CONSOLE

:: Check if compilation was successful
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilation successful!
    echo Copying SDL2.dll to bin directory...
    copy "external\SDL2\lib\x64\SDL2.dll" "bin\"

    echo Creating shader directory...
    if not exist "bin\assets\shaders" mkdir "bin\assets\shaders"

    echo Copying shader files...
    copy "assets\shaders\basic.vert" "bin\assets\shaders\"
    copy "assets\shaders\basic.frag" "bin\assets\shaders\"
    echo.
    echo Running the program:
    echo.
    bin\sdl_app.exe
) else (
    echo.
    echo Compilation failed!
)

pause
