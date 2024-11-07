#[[ cmake_minimum_required(VERSION 3.10) 
project(VolumetricViewer)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
    third-party/happly/happly.h
    third-party/glm/glm/*.h
    third-party/glm/glm/*.cpp
    third-party/glew/src/glew.c
    third-party/glew/include/*.h
)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(VolumetricViewer/third-party)

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
endif()]]

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
    src/*.h
    third-party/happly/happly.h
    third-party/glm/glm/*.h
    third-party/glm/glm/*.cpp
    third-party/glew/src/glew.c
    third-party/glew/include/*.h
    #[[ third-party/glfw/include/*.h ]]
    #[[ third-party/glfw/include/*.h ]]
    #[[ third-party/glfw/include/*.h ]]
    #[[ third-party/glfw/src/*.c ]]
    #[[ third-party/glfw/src/*.h ]]
)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/glm)
include_directories(${PROJECT_SOURCE_DIR}/third-party/glfw/include)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 3.3 REQUIRED)

# Specify GLFW library path for Windows
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/third-party/glfw/lib-static-ucrt)

# Add the executable
add_executable(BVH-VIEWER ${SOURCES})

# Link libraries
target_link_libraries(BVH-VIEWER
    ${OPENGL_gl_LIBRARY}
    glfw
)

# Optionally include GLM (if using)
find_package(glm CONFIG REQUIRED)
if (glm_FOUND)
    target_link_libraries(BVH-VIEWER glm::glm)
endif()

# Ensure the DLL is available in the output directory
#[[ add_custom_command(TARGET BVH-VIEWER POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${GLFW_DIR}/glfw3.dll $<TARGET_FILE_DIR:BVH-VIEWER>)]]


