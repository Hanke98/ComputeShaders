cmake_minimum_required(VERSION 3.16)
project(ComputeShaders)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
endif()
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})

add_subdirectory(Render)
set(third_libs glfw GLEW)
set(libs RENDER)
add_executable(ComputeShaders main.cpp)
target_link_libraries(ComputeShaders ${third_libs} ${libs})