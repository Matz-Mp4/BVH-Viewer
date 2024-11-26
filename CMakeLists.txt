cmake_minimum_required(VERSION 3.10)
project(BVH-VIEWER)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/bvh
    ${PROJECT_SOURCE_DIR}/include/objects
    ${PROJECT_SOURCE_DIR}/include/objects/shapes
    ${PROJECT_SOURCE_DIR}/include/material
    ${PROJECT_SOURCE_DIR}/include/camera
    ${PROJECT_SOURCE_DIR}/include/camera/camera-types
    ${PROJECT_SOURCE_DIR}/include/math
    ${PROJECT_SOURCE_DIR}/include/light
    ${PROJECT_SOURCE_DIR}/include/GLSL/export-data
    ${PROJECT_SOURCE_DIR}/include/GLSL/utils
    ${PROJECT_SOURCE_DIR}/include/GLSL/export-data/export-camera
    ${PROJECT_SOURCE_DIR}/include/GLSL/export-data/export-object
    ${PROJECT_SOURCE_DIR}/include/GLSL/export-data/export-light
    ${PROJECT_SOURCE_DIR}/third-party/happly
    ${PROJECT_SOURCE_DIR}/third-party/imgui
)
include_directories(${INCLUDE_DIRS})

# Helper function to collect .cpp files into a variable
function(collect_sources VARIABLE DIRECTORY)
    file(GLOB_RECURSE FILES "${DIRECTORY}/*.cpp")
    set(${VARIABLE} ${${VARIABLE}} ${FILES} PARENT_SCOPE)
endfunction()

# Collect source files into the SOURCES variable
set(SOURCES)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/bvh)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/objects)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/objects/shapes)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/material)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/camera)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/camera/camera-types)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/math)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/math/utils)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/light)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/GLSL/export-data)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/GLSL/utils)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/GLSL/export-data/export-camera)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/GLSL/export-data/export-object)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/src/GLSL/export-data/export-light)
collect_sources(SOURCES ${PROJECT_SOURCE_DIR}/third-party/imgui)

# Add header-only files to SOURCES
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/third-party/happly/happly.h)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add executable and link sources
add_executable(BVH-VIEWER ${SOURCES})

# Link libraries
target_link_libraries(BVH-VIEWER
    OpenGL::GL
    glfw
    GLEW::GLEW
)


#[[ set(CMAKE_CXX_FLAGS  -g -O3) ]]
#[[ add_compile_options(CMAKE_CXX_FLAGS) ]]
    add_compile_options(-O3)
    add_compile_options(-g)

