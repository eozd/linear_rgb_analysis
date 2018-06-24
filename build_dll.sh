#!/usr/bin/env bash

SRC="src/linear_regression.c src/rgb_analysis.c src/utils.c"

i686-w64-mingw32-gcc -DWINDOWS -static-libgcc -O3 -shared -fPIC $SRC -lm -o build/rgb_analysis.dll
