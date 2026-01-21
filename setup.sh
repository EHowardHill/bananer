#!/bin/bash

set -e

sudo apt update -y
sudo apt install -y build-essential git mingw-w64

git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src

make PLATFORM=PLATFORM_DESKTOP OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar