cmake_minimum_required(VERSION 3.10)
project(VolumetricViewer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
    third-party/rply-1.1.4/rply.h
    third-party/rply-1.1.4/rply.c
    third-party/rply-1.1.4/rplyfile.h
)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 3.3 REQUIRED)

# Find GLEW
find_package(GLEW REQUIRED)

# Add the executable
add_executable(VolumetricViewer ${SOURCES})

# Link libraries
target_link_libraries(VolumetricViewer
    GLEW::GLEW
    glfw
    ${OPENGL_gl_LIBRARY}
)

# Optionally include GLM (if using)
find_package(glm CONFIG REQUIRED)
if (glm_FOUND)
    target_link_libraries(VolumetricViewer glm::glm)
endif()

