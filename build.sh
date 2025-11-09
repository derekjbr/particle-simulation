# Building GLFW
mkdir -p ./external/glfw/src/build
cmake -B ./external/glfw/src/build -D CMAKE_INSTALL_PREFIX=./external/glfw ./external/glfw/src
cd ./external/glfw/src/build
make install -j4
