#!/bin/bash

set -e

x86_64-w64-mingw32-gcc main.c -o game.exe \
    -I ./raylib/src \
    -L ./raylib/src \
    -lraylib -lopengl32 -lgdi32 -lwinmm -static