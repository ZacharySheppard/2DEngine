cmake_minimum_required(VERSION 3.21)
project(2DEngine)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)


add_subdirectory(src)