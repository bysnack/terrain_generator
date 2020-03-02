cmake_minimum_required(VERSION 3.2)
project(opengl)
set(OPENGL_VERSION_MAJOR 1)
set(OPENGL_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(opengl main.cpp)

include_directories(opengl ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(opengl ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )