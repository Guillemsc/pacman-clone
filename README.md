[![Build](https://github.com/Guillemsc/pacman-clone/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Guillemsc/pacman-clone/actions/workflows/cmake-multi-platform.yml)

<img width="1640" height="664" alt="logo" src="https://github.com/user-attachments/assets/ecd61182-7382-4f7e-accc-9c49940e7d10" />

A **Pac-Man** clone done as an example of the **C++** game engine framework: **GEngine**. 

https://github.com/user-attachments/assets/d4df2ee9-591d-46cc-9c47-51ff3a4386df

## Building:

### Prerequisites

- C++20 compatible compiler (GCC, Clang, MSVC).
- [CMake](https://cmake.org/) ≥ 3.31.

## Structure:
### Folder Structure:
The project is divided between the core [GEngine folder](https://github.com/Guillemsc/pacman-clone/tree/main/GEngine), and the [PacMan game folder](https://github.com/Guillemsc/pacman-clone/tree/main/PacMan).

Thid party tools used by the engine can be found at [GEngine/vendor/](https://github.com/Guillemsc/pacman-clone/tree/main/GEngine/vendor)

### Entry point:
Main program entry point can be found at [PacMan/src/Bootstrap/main.cpp](https://github.com/Guillemsc/pacman-clone/blob/main/PacMan/src/PacMan/Bootstrap/main.cpp).
Here, GEngine is initialized, and PacMan is loaded and run.

### Contexts:
The game overall structure is divided in [contexts](https://github.com/Guillemsc/pacman-clone/tree/main/PacMan/src/PacMan/Contexts). A context is an abstraction of an independent chunk of a game.
The game has three main contexts: 
  - [Shared context](https://github.com/Guillemsc/pacman-clone/blob/main/PacMan/src/PacMan/Contexts/SharedContext.cpp): contains essential parts used by all the different game contexts.
  - [Meta context](https://github.com/Guillemsc/pacman-clone/blob/main/PacMan/src/PacMan/Contexts/MetaContext.cpp): context that contains all the menus that the player finds before the main gameplay (main menu for example).
  - [Gameplay context](https://github.com/Guillemsc/pacman-clone/blob/main/PacMan/src/PacMan/Contexts/GameplayContext.cpp): main gameplay of the game.

## Third party
- Raylib (OS layer and rendering)
- ImGui (editor ui)
- Glm (math)
- Spdlog (logging)
- Tmxlite (tiled importing)

## References:
- [Game Internals: Understanding Pac-Man Ghost Behavior](https://gameinternals.com/understanding-pac-man-ghost-behavior)

