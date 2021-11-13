#!/bin/bash
if [ "$1" = "clean" ]; then
    echo [0] Deleting older cmake cache...
    rm build -rf
    rm bin -rf
fi

echo [1] Building Makefiles...
cmake -G "Unix Makefiles" -H. -B./build

echo [2] Running Make...
make

echo [3] Done!
