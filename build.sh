#!/bin/bash
if [ "$1" = "clean" ]; then
    echo [0] Deleting older cmake cache...
    rm CMakeFiles -rf
    rm cmake_install.cmake -f
    rm CMakeCache.txt -f
    rm Makefile -f
fi

echo [1] Building Makefiles...
cmake -G "Unix Makefiles" -H. -B.

echo [2] Running Make...
make

echo [3] Done building binary in bin/main
