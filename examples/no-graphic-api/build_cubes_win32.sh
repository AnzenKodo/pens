#!/bin/bash
# build_cubes_win32.sh - Cross-compile 3-Cube Example for Windows using MinGW-w64
set -e

CROSS_CC="${CROSS_CC:-x86_64-w64-mingw32-gcc}"
CFLAGS="-std=c11 -Wall -Wextra -Wno-unused-parameter -O2"
LDFLAGS="-luser32 -lgdi32"

echo "=== Compiling Shaders with glslc ==="
glslc -O cube.vert -o cube_vert.spv
glslc -O cube.frag -o cube_frag.spv
glslc -O -mfmt=c cube.vert -o cube_vert_spv.h
glslc -O -mfmt=c cube.frag -o cube_frag_spv.h
echo "Shader compilation OK."

echo "=== Cross-compiling for Windows (${CROSS_CC}) ==="
${CROSS_CC} ${CFLAGS} -o cube_example.exe cube_example.c ${LDFLAGS}
echo "Build complete: cube_example.exe"
echo ""
echo "Run on Windows or via Wine: wine cube_example.exe"
