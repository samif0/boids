cmake_minimum_required(VERSION 3.15)

# Set the toolchain file using the environment variable
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable is not set")
endif()

set(TARGET_OS "unknown")
set(TARGET_ARCH "unknown")

if(WIN32)
    set(TARGET_OS "windows")
elseif(APPLE)
    set(TARGET_OS "osx")
elseif(UNIX AND NOT APPLE)
    set(TARGET_OS "linux")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$")
    set(TARGET_ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(i[3-6]86|x86)$")
    set(TARGET_ARCH "x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64|ARM64)$")
    set(TARGET_ARCH "arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|ARM)$")
    set(TARGET_ARCH "arm")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(VCPKG_TARGET_TRIPLET "${TARGET_ARCH}-${TARGET_OS}" CACHE STRING "")
set(VCPKG_MANIFEST_DIR ${CMAKE_SOURCE_DIR})

project(boids)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(boids ${SOURCES})

find_package(Freetype REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(boids PRIVATE
    Freetype::Freetype
    sfml-system
    sfml-network 
    sfml-graphics 
    sfml-window
    sfml-audio
)

