#!/bin/sh
rm bootloader.*
make clean
rm CMakeCache.txt
rm program.*
rm -rf CMakeFiles
find . -name "Makefile" -type f -print -exec rm -rf {} \;
find . -name "cmake_install.*" -type f -print -exec rm -rf {} \;
find . -type d -name "CMakeFiles" -exec rm -rf {} +
# cmake .
# make