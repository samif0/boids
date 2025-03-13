# Boids Project Setup

## Prerequisites
- CMake
- vcpkg
- C++ compiler
- Note: CMake Preset assumes Linux/MacOSX dev setup, update generator if using Windows.

## Setup Steps

1. Install vcpkg and set VCPKG_ROOT environment variable:
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

2. Build 
```bash
cmake -B build -S .
cmake --build build
```

3. Configure VSCode .vscode/Settings.json (optional, CMakePresets.json already)
```json
{
    "cmake.sourceDirectory": "${workspaceFolder}",
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}scripts/buildsystems/vcpkg.cmake"
    },
    "cmake.generator": "MinGW Makefiles", //TODO: Change based on preferred generator. i.e. Ninja ...
    "cmake.buildDirectory": "${workspaceFolder}/build", //TODO: Update if you have don't have a parent folder for your project.
    "cmake.configureArgs": [],
    "cmake.configureEnvironment": {},
    "cmake.buildEnvironment": {},
    "cmake.environment": {}
}
```
