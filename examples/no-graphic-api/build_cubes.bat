@echo off
REM build_cubes.bat - Build 3-Cube Example on Windows (MSVC cl.exe or Clang/GCC)
REM
REM Compiles shaders if glslc is available, then compiles cube_example.c.
REM Zero Vulkan SDK headers required at compile time (loads vulkan-1.dll dynamically).

where glslc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Compiling Shaders with glslc ===
    glslc -O cube.vert -o cube_vert.spv
    glslc -O cube.frag -o cube_frag.spv
    glslc -O -mfmt=c cube.vert -o cube_vert_spv.h
    glslc -O -mfmt=c cube.frag -o cube_frag_spv.h
    echo Shaders compiled successfully.
) else (
    echo [NOTE] glslc not found in PATH; using pre-generated shader headers.
)

where cl >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building 3-Cube Example with MSVC (cl.exe) ===
    cl /nologo /std:c11 /W3 /O2 /Fe:cube_example.exe cube_example.c user32.lib gdi32.lib
    if %ERRORLEVEL% equ 0 (
        echo Build complete: cube_example.exe
        echo Run with: cube_example.exe
    )
    exit /b %ERRORLEVEL%
)

where clang >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building 3-Cube Example with Clang ===
    clang -std=c11 -Wall -Wextra -O2 -o cube_example.exe cube_example.c -luser32 -lgdi32
    if %ERRORLEVEL% equ 0 (
        echo Build complete: cube_example.exe
        echo Run with: cube_example.exe
    )
    exit /b %ERRORLEVEL%
)

where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building 3-Cube Example with GCC ===
    gcc -std=c11 -Wall -Wextra -O2 -o cube_example.exe cube_example.c -luser32 -lgdi32
    if %ERRORLEVEL% equ 0 (
        echo Build complete: cube_example.exe
        echo Run with: cube_example.exe
    )
    exit /b %ERRORLEVEL%
)

echo [ERROR] No supported C compiler (cl, clang, or gcc) found in PATH.
exit /b 1
