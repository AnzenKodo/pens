#!/usr/bin/env bash

set -o errexit
set -o nounset
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrae;
fi
cd "$(dirname "$0")"

# Create build dir
DIR="build"
if [ ! -d "$DIR" ]; then
    mkdir "$DIR"
    echo "Directory $DIR created."
fi

filename="main"

nasm -f elf64 $filename.asm -o build/$filename.o
ld build/$filename.o -o build/$filename
build/$filename
