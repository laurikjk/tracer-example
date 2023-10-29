#!/bin/bash

# Remove any existing pybind11 directory
rm -rf pybind11

# Clone fresh pybind11
git clone https://github.com/pybind/pybind11.git

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake and make
cmake ..
make

echo "Build completed!"
