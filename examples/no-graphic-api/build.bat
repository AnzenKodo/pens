@echo off
REM build.bat - Build "No Graphics API" example on Windows (MSVC cl.exe or Clang/GCC)
REM
REM No Vulkan SDK needed! The library loads vulkan-1.dll dynamically at runtime.
REM Requires a C compiler and a Vulkan 1.3 driver installed.

where cl >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building with MSVC (cl.exe) ===
    cl /nologo /std:c11 /W3 /O2 /Fe:example.exe example.c
    if %ERRORLEVEL% equ 0 (
        echo Build complete: example.exe
        echo Run with: example.exe
    )
    exit /b %ERRORLEVEL%
)

where clang >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building with Clang ===
    clang -std=c11 -Wall -Wextra -O2 -o example.exe example.c
    if %ERRORLEVEL% equ 0 (
        echo Build complete: example.exe
        echo Run with: example.exe
    )
    exit /b %ERRORLEVEL%
)

where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo === Building with GCC ===
    gcc -std=c11 -Wall -Wextra -O2 -o example.exe example.c
    if %ERRORLEVEL% equ 0 (
        echo Build complete: example.exe
        echo Run with: example.exe
    )
    exit /b %ERRORLEVEL%
)

echo [ERROR] No supported C compiler (cl, clang, or gcc) found in PATH.
exit /b 1
