cmake_minimum_required(VERSION 3.16)
project(ComputeShaders)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(Render)
set(third_libs glfw GLEW)
add_executable(ComputeShaders main.cpp)
target_link_libraries(ComputeShaders ${third_libs})