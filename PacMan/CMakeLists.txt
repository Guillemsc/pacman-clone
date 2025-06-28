cmake_minimum_required(VERSION 3.31)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)

add_executable(PacMan src/PacMan/Bootstrap/main.cpp
        src/PacMan/Games/PacManGame.h
        src/PacMan/Games/PacManGame.cpp
        src/PacMan/Systems/MapMovementSystem.cpp
        src/PacMan/Systems/MapMovementSystem.h)

target_link_libraries(PacMan PRIVATE GEngineCore)

target_include_directories(PacMan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
