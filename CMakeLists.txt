cmake_minimum_required(VERSION 3.10)
project(BVH-VIEWER)

# Enable compile commands export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    third-party/happly/happly.h
    third-party/imgui/*.cpp
)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/happly)
include_directories(${PROJECT_SOURCE_DIR}/third-party/imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(BVH-VIEWER ${SOURCES})

# Link libraries
target_link_libraries(BVH-VIEWER
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW::GLEW
    ${OPENGL_gl_LIBRARY}
)
