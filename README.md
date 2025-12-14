[![Build](https://github.com/Guillemsc/pacman-clone/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Guillemsc/pacman-clone/actions/workflows/cmake-multi-platform.yml)

<img width="1640" height="664" alt="logo" src="https://github.com/user-attachments/assets/ecd61182-7382-4f7e-accc-9c49940e7d10" />

A simple **Pac-Man** clone done as an example of the **C++** game engine framework: **GEngine**. 

> ⚠️ **This project is a Work In Progress** — features and gameplay are still under active development.

## Building:

### Prerequisites

- C++20 compatible compiler (GCC, Clang, MSVC)
- [CMake](https://cmake.org/) ≥ 3.31

## Structure:
### Folder Structure:
The project is divided between the core [GEngine folder](https://github.com/Guillemsc/pacman-clone/tree/main/GEngine), and the [PacMan game folder](https://github.com/Guillemsc/pacman-clone/tree/main/PacMan).

Thid party tools used by the engine can be found at [GEngine/vendor/](https://github.com/Guillemsc/pacman-clone/tree/main/GEngine/vendor)

### Entry point:
Main program entry point can be found at [PacMan/src/Bootstrap/main.cpp](https://github.com/Guillemsc/pacman-clone/blob/main/PacMan/src/PacMan/Bootstrap/main.cpp).
Here, GEngine is initialized, and PacMan is loaded and run.

## Third party
- Raylib (OS layer and rendering)
- ImGui (editor ui)
- Glm (math)
- Spdlog (logging)
- Tmxlite (tiled importing)

## References:
- [Game Internals: Understanding Pac-Man Ghost Behavior](https://gameinternals.com/understanding-pac-man-ghost-behavior)

