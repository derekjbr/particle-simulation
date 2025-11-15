cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation VERSION 1.0 LANGUAGES CXX C)

# Find OpenGL
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Try to find GLFW
if(GLFW_PATH)
    message(STATUS "Looking for GLFW in specified path: ${GLFW_PATH}")
    set(glfw3_DIR "${GLFW_PATH}/lib/cmake/glfw3" CACHE PATH "Path to GLFW CMake config files")
    find_package(glfw3 QUIET)
    if(NOT glfw3_FOUND)
        message(FATAL_ERROR "GLFW not found in specified path: ${GLFW_PATH} (looked in ${glfw3_DIR})")
    endif()
else()
    message(STATUS "Looking for system GLFW installation...")
    find_package(glfw3 QUIET)
    
    if(NOT glfw3_FOUND)
        message(STATUS "System GLFW not found, trying local copy...")
        set(LOCAL_GLFW "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")
        set(glfw3_DIR "${LOCAL_GLFW}/lib/cmake/glfw3" CACHE PATH "Path to GLFW CMake config files")
        find_package(glfw3 REQUIRED)
    endif()
endif()

# Glad setup
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
set(GLAD_SRC "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")

include_directories(${GLAD_INCLUDE_DIR})

# Add Subdirectories
add_subdirectory(Renderer)
add_subdirectory(Utils)

# Main executable
add_executable(ParticleSimulation main.cpp ${GLAD_SRC})

# Link against GLFW (includes will be handled by the imported target)
target_link_libraries(ParticleSimulation 
    PRIVATE 
    OpenGL::GL 
    glfw
    Shader)

# Copy Resources to build directory
add_custom_command(TARGET ParticleSimulation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    "Resources"
    COMMENT "Copying Resources to build directory"
)
