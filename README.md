# Bananer

Bananer is a set of header files that can be used to easily convert a Butano (https://github.com/GValiente/butano) library into a Raylib project.

It is still in ALPHA and only supports a small subset of the Butano API, mainly 2D code.

**Planned additions:**
- Affine bg support
- 3D support

Note: Bananer is not directly associated in any way with Butano.

## How to use

This only works with Debian/Ubuntu-based systems, either natively or through WSL2. It currently only produces binaries for Windows x64.

1. Run `setup.sh` in order to pull the relevant files onto your system.
2. Add your project files to the following folders: "src" for `.cpp`, "headers" for `.h`, "graphics" for graphics, and "audio" for audio.
3. Run `build_win64.sh` in order to compile your project for Windows.

Enjoy!

# License

All existing licenses, including the most permissive licenses, seem to request that the original copyright and license text be included. Let it be said in writing that I do not care for even this, do whatever you want with this code.
