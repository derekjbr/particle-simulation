#!/usr/bin/env bash

# Default Build Values
rebuild=false
glfw_path="./external/glfw"

# Print usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Options:"
    echo "  glfw_path=PATH    Path to GLFW installation (default: ./external/glfw)"
    echo "  rebuild=true      Rebuild GLFW from source (only if using local GLFW)"
    exit 1
}

# Parse Arguments
for arg in "$@"; do
    case $arg in
        glfw_path=*)
            glfw_path="${arg#*=}"
            shift
            ;;
        rebuild=*)
            rebuild="${arg#*=}"
            shift
            ;;
        help|--help|-h)
            usage
            ;;
        *)
            echo "Unknown option: $arg"
            usage
            ;;
    esac
done

# Building GLFW if using local copy and rebuild is requested
if [ "$rebuild" = true ] && [ "$glfw_path" = "./external/glfw" ]; then
    echo "Rebuilding local GLFW..."
    mkdir -p ./external/glfw/src/build
    cmake -B ./external/glfw/src/build -D CMAKE_INSTALL_PREFIX=./external/glfw ./external/glfw/src
    cd ./external/glfw/src/build
    make install -j4
    cd ../../../..
fi

# Build the project
echo "Building project with GLFW from: $glfw_path"
cmake -B ./build -D CMAKE_BUILD_TYPE=Debug -D GLFW_PATH="$glfw_path"
cmake --build ./build -j4
