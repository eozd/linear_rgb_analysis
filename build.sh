#!/usr/bin/env bash

SRC="src/main.c src/rgb_analysis.c src/linear_regression.c src/utils.c"

i686-w64-mingw32-gcc -DWINDOWS -O3 -static-libgcc -Iinclude $SRC -lm -o build/analyze_rgb
gcc -DLINUX -O3 -Iinclude $SRC -lm -o build/a.out
