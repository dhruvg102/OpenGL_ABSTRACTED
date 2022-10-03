cmake_minimum_required(VERSION 3.14)

project(OPENGL_ABSTRACTED)


file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)



add_subdirectory(external/glfw/)
add_subdirectory(external/glad/)
add_subdirectory(external/imgui/)

# set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
# set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
# set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
# set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )
# set( BUILD_EXAMPLES OFF CACHE BOOL  "RCCpp libsonly" )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})


include_directories(${CMAKE_SOURCE_DIR}/external/glm PUBLIC glm)

target_include_directories(${PROJECT_NAME} PUBLIC external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)


target_include_directories(${PROJECT_NAME} PUBLIC external/imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
