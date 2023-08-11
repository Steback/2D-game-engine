# Game made with SDL2 and Lua

![Game Image]( images/img-game-1.png )

A simple game that I learned in the [Fundamentals of 2D Game Engines with C++ SDL and Lua]( https://www.udemy.com/course/cpp-2d-game-engine/ ) course. In the game i use SDL2 for the game engine, and Lua for data and script loading.

In the future, I plan to create a map editor for the game, using C ++ and SDL2.

## Dependences
1. [SDL2 2.26.5](https://www.libsdl.org/)
2. [Lua 5.4.4](https://www.lua.org/)
3. [Sol 3.3.0](https://github.com/ThePhD/sol2)
4. [OpenGL Mathematics(GLM) 0.9.8](https://glm.g-truc.net/0.9.9/index.html)

## Build
All the third-party dependencies are installed using [conan](https://conan.io/)

### Requirements
* CMake >= 3.18
* conan >= 2.0.5

First execute the setup script for install all necessary dependencies

### Linux
* GCC >= 13

```
./setup.sh
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=build/release/conan_toolchain.cmake -S . -B ~/build/release
cmake --build ~/build/release --target RavenEditor -- -j X
```

### Window
* Visual Studio >= 22
```
.\setup.bat
cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="build\release\conan_toolchain.cmake" -S . -B ~/build/release
cmake --build ~/build/release --target RavenEditor --config Release
```