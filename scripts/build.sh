#!/bin/bash
set -x #echo on

if [ ! -f third_party/libwally-core/src/config.h ]; then
    cd third_party/libwally-core
    ./tools/autogen.sh
    ./configure
    make
    cp ../../cmake/libwally-core/CMakeLists.txt .
    cmake .
    cd ../..
fi

mkdir -p build
cd build
cmake ..
make
cd ..