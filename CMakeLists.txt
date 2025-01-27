cmake_minimum_required(VERSION 3.15)
project(boids)
set(CMAKE_CXX_STANDARD 17)
set(VCPKG_TARGET_TRIPLET "arm64-osx")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(FREETYPE_INCLUDE_DIRS "$ENV{VCPKG_ROOT}/installed/arm64-osx/include/freetype")
set(FREETYPE_LIBRARY "$ENV{VCPKG_ROOT}/installed/arm64-osx/lib/libfreetype.a")
set(FREETYPE_DIR "$ENV{VCPKG_ROOT}/installed/arm64-osx/share/freetype")
set(SFML_DIR "$ENV{VCPKG_ROOT}/installed/arm64-osx/share/sfml")

add_executable(boids src/main.cpp)

find_package(Freetype REQUIRED)
target_link_libraries(boids PRIVATE Freetype::Freetype)

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
target_link_libraries(boids PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

