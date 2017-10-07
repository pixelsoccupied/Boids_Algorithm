cmake_minimum_required(VERSION 3.8)
project(Boids_Algorithm)
find_package(glfw3 3.2.1 REQUIRED)
find_package (OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -L/usr/local/lib -framework Cocoa -framework IOKit -framework CoreVideo -lglfw3")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
link_directories(/usr/local/lib)


find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -framework OpenGL")

set(SOURCE_FILES main.cpp Engine.cpp Engine.h Boid.cpp Boid.h Flock.cpp Flock.h)
add_executable(Boids_Algorithm ${SOURCE_FILES})