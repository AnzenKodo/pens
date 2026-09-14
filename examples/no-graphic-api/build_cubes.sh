#!/bin/bash
# build_cubes.sh - Compile shaders and build the 3-cube example
set -e

CC="${CC:-cc}"
CFLAGS="-std=c11 -Wall -Wextra -Wno-unused-parameter -g -O2"
LDFLAGS="-ldl -lm -lxcb"

echo "=== Compiling Shaders with glslc ==="
glslc -O cube.vert -o cube_vert.spv
glslc -O cube.frag -o cube_frag.spv
glslc -O -mfmt=c cube.vert -o cube_vert_spv.h
glslc -O -mfmt=c cube.frag -o cube_frag_spv.h
echo "Shader compilation OK."

echo "=== Building 3-Cube Example ==="
${CC} ${CFLAGS} -o cube_example cube_example.c ${LDFLAGS}
echo "Build complete: ./cube_example"
echo ""
echo "Run with: ./cube_example"
