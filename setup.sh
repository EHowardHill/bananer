#!/bin/bash

set -e

sudo apt update -y
sudo apt install -y build-essential git mingw-w64
sudo apt install -y cmake pkgconf libreadline8 libusb-0.1 libgpgme11 libarchive-tools fakeroot

git clone https://github.com/raysan5/raylib.git raylib_win64
git clone https://github.com/psxdev/raylib4Dreamcast

git clone https://github.com/raylib4Consoles/raylib -b dreamcast raylib4Dreamcast
git clone https://github.com/raylib4Consoles/raylib4Psp raylib4Psp

cd ~
mkdir -p ~/pspdev
wget https://github.com/pspdev/pspdev/releases/latest/download/pspdev-ubuntu-latest-x86_64.tar.gz
tar -xzf pspdev-ubuntu-latest-x86_64.tar.gz -C ~/pspdev
rm pspdev-ubuntu-latest-x86_64.tar.gz

# Make Raylib-Win64
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP OS=Windows_NT CC=x86_64-w64-mingw32-gcc AR=x86_64-w64-mingw32-ar