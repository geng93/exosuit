#!/bin/bash
mkdir build
cd ./build
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release BUILD_SHARED_LIB=ON -D CPU_ONLY=ON -D USE_CUDNN=OFF CUDA_ARCH_NAME=Auto -DBLAS=open -D USE_OPENMP=ON -D BUILD_python=OFF -D BUILD_python_layer=OFF -D BUILD_matlab=OFF ..
#-j4 where 4 is the number of parallel threads for compilation
make all -j4
make test
make runtest
cd ..
# ./build/multivariate
