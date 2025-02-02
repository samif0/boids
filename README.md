# Boids Project Setup

Currently setup for macosx

## Prerequisites
- CMake
- vcpkg
- C++ compiler

## Setup Steps

1. Set VCPKG_ROOT environment variable:
```bash
export VCPKG_ROOT=/path/to/vcpkg
```
2. Install dependencies using vcpkg:
```bash
vcpkg install sfml
vcpkg install freetype
```
3. Build 
```bash
cmake -B build && cmake --build build
```
4. (Optional) VS Code configuration 
- Add to includePath: "${VCPKG_ROOT}/installed/arm64-osx/include"

## Running 

```bash
./build/boids
```
