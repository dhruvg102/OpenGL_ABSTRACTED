cmake_minimum_required(VERSION 3.14)

project(OPENGL_ABSTRACTED)


file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)


add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory(external/glfw/)
add_subdirectory(external/glad/)

include_directories(${CMAKE_SOURCE_DIR}/external/glm PUBLIC glm)


target_include_directories(${PROJECT_NAME} PUBLIC external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
