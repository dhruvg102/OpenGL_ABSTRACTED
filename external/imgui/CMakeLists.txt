cmake_minimum_required(VERSION 3.4)
project(Imgui)

add_library(imgui STATIC)

include_directories(${PROJECT_NAME} PUBLIC ../glfw/include)
link_libraries(${PROJECT_NAME} PUBLIC glfw)

target_sources( imgui
                PRIVATE
                    imgui/imgui_demo.cpp
                    imgui/imgui_draw.cpp
                    imgui/imgui_tables.cpp
                    imgui/imgui_widgets.cpp
                    imgui/imgui.cpp

                PRIVATE
                    imgui/imgui_impl_opengl3.cpp
                    imgui/imgui_impl_glfw.cpp
                )
target_include_directories(imgui PUBLIC imgui)



