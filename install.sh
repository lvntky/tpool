#!/bin/bash

set -e

INSTALL_PREFIX="/usr/local"
INCLUDE_DIR="$INSTALL_PREFIX/include"
LIB_DIR="$INSTALL_PREFIX/lib"
PKGCONFIG_DIR="$LIB_DIR/pkgconfig"

echo "Building tpool..."

# Check and build if build folder doesn't exist
if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
    make
    cd ..
else
    cd build
    make
    cd ..
fi

echo "Installing tpool..."

# Install header
sudo install -Dm644 include/tpool.h "$INCLUDE_DIR/tpool.h"

# Install library
sudo install -Dm644 build/libtpool.a "$LIB_DIR/libtpool.a"

# Install pkg-config file
sudo install -Dm644 build/tpool.pc "$PKGCONFIG_DIR/tpool.pc"

# echo "tpool installed system-wide!"
