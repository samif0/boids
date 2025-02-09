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
    "cmake.sourceDirectory": "C:/Users/samif/Projects/boids", //TODO: Update source directory
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}scripts/buildsystems/vcpkg.cmake"
    },
    "cmake.generator": "MinGW Makefiles", //TODO: Change based on preferred generator. i.e. Ninja ...
    "cmake.buildDirectory": "${workspaceFolder}/${workspaceFolderBasename}/build", //TODO: Update if you have don't have a parent folder for your project.
    "cmake.configureArgs": [],
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
