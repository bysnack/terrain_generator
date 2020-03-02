cmake_minimum_required(VERSION 3.2)
project(terrain)
set(TERRAIN_VERSION_MAJOR 1)
set(TERRAIN_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(terrain main.cpp)

include_directories(terrain ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(terrain ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )