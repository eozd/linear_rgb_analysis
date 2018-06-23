#!/usr/bin/env bash

SRC="src/linear_regression.c src/utils.c src/rgb_analysis.c"

i686-w64-mingw32-gcc -DWINDOWS -static-libgcc -O3 -shared -fPIC $SRC -o build/rgb_analysis.dll
