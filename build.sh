#!/bin/bash
# clear
mkdir -p build
cd ./build
cmake -G "Unix Makefiles" ..
#-j4 where 4 is the number of parallel threads for compilation
make all -j4
