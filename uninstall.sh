#!/bin/bash

set -e

INSTALL_PREFIX="/usr/local"
INCLUDE_DIR="$INSTALL_PREFIX/include"
LIB_DIR="$INSTALL_PREFIX/lib"
PKGCONFIG_DIR="$LIB_DIR/pkgconfig"

echo "Uninstalling tpool..."

# Remove header
sudo rm -f "$INCLUDE_DIR/tpool.h"

# Remove static library
sudo rm -f "$LIB_DIR/libtpool.a"

# Remove pkg-config file
sudo rm -f "$PKGCONFIG_DIR/tpool.pc"

echo "tpool uninstalled from system."
