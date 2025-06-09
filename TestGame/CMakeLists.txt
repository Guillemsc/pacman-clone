cmake_minimum_required(VERSION 3.31)
project(TestGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(TestGame src/Bootstrap/main.cpp
        src/Games/TestGame.h
        src/Games/TestGame.cpp)

target_link_libraries(TestGame PRIVATE GEngineCore)
