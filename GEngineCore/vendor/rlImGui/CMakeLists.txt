project(rlImGui)

add_library(rlImGui STATIC rlImGui.cpp)

target_include_directories(rlImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rlImGui PUBLIC raylib)
target_link_libraries(rlImGui PUBLIC imgui)