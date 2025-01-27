# Boids Project Setup

## Prerequisites
- CMake
- vcpkg
- C++ compiler

## Setup Steps

1. Set VCPKG_ROOT environment variable:
```bash
export VCPKG_ROOT=/path/to/vcpkg


2. Install dependencies using vcpkg:

- vcpkg install sfml:arm64-osx
- vcpkg install freetype:arm64-osx

3. Build 

cmake -B build && cmake --build build

4. (Optional) VS Code configuration 

- Add to includePath: "${VCPKG_ROOT}/installed/arm64-osx/include"


## Running 

./build/boids

