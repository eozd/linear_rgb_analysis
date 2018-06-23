#!/usr/bin/env bash

SRC="src/main.c src/rgb_analysis.c src/utils.c src/linear_regression.c"

i686-w64-mingw32-gcc -DWINDOWS -static-libgcc $SRC -o build/analyze_rgb
gcc -DLINUX $SRC -o build/a.out
