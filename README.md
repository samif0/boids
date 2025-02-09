# Boids Project Setup

Currently setup for macosx

## Prerequisites
- CMake
- vcpkg
- C++ compiler

## Setup Steps

1. Install vcpkg and set VCPKG_ROOT environment variable:
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

2. Install dependencies using vcpkg:
```bash
vcpkg integrate install
```
3. Build 
```bash
cmake -B build -S .
```
4. Configure VS Code

For VS Code automated cmake builds create: .vscode/Settings.json
```json
{
    "cmake.sourceDirectory": "C:/Users/samif/Projects/boids",
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}scripts/buildsystems/vcpkg.cmake"
    },
    "cmake.generator": "MinGW Makefiles",
    "cmake.buildDirectory": "${workspaceFolder}/${workspaceFolderBasename}/build",
    "cmake.configureArgs": [],  // Remove any extra args
    "cmake.configureEnvironment": {},
    "cmake.buildEnvironment": {},
    "cmake.environment": {}
}
```

Update/Create .vscode/c_cpp_properties.json to have proper include paths if necessary.

## Running 

```bash
./build/boids
```
