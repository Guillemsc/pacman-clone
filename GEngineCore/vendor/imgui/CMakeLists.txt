project(imgui)

add_library(imgui STATIC
        imgui.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui_demo.cpp
)

# C++11 mínimo
target_compile_features(imgui PUBLIC cxx_std_11)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
