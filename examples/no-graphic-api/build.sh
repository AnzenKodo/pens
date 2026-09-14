#!/bin/bash
# build.sh - Build the "No Graphics API" example
#
# No Vulkan SDK needed! The library loads libvulkan.so dynamically.
# Only requires: a C compiler, libdl (dlopen/dlsym), and a Vulkan driver installed.

set -e

CC="${CC:-cc}"
CFLAGS="-std=c11 -Wall -Wextra -Wno-unused-parameter -g -O0"
LDFLAGS="-ldl -lm"

echo "=== Building No Graphics API Example ==="
echo "Compiler: ${CC}"

${CC} ${CFLAGS} -o example example.c ${LDFLAGS}

echo "Build complete: ./example"
echo ""
echo "Run with: ./example"
echo "Note: Requires Vulkan 1.3 driver installed (libvulkan.so)"
