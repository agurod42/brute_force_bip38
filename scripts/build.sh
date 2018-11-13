#!/bin/bash

# Install dependencies

echo "Installing dependencies..."
uname="$(uname -s)"
case "${uname}" in
    Linux*)     sudo apt-get install -y build-essential cmake3 libtool
                ;;
    Darwin*)    brew install autoconf automake cmake libtool
                ;;
    *)          echo "Error: cannot build on ${uname}"
                exit 1
esac

# Build libwally-core

if [ ! -f third_party/libwally-core/src/config.h ]; then
    echo "Building libwally-core..."
    cd third_party/libwally-core
    ./tools/autogen.sh
    ./configure
    make
    cp ../../cmake/libwally-core/CMakeLists.txt .
    cmake .
    cd ../..
fi

# Build brute_force_bip38

echo "Building brute_force_bip38..."
mkdir -p build
cd build
cmake ..
make
cd ..

# Done :)
echo "Done."