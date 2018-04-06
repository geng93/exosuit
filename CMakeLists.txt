# App_WalkingModel is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 2.4.3)
PROJECT(caffe_test)

set (caffe_test_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set (caffe_test_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

# set (BULLET_PHYSICS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/bullet3-2.83.7)
# set (BULLET_PHYSICS_BUILD_DIR ${PROJECT_SOURCE_DIR}/build_bullet)

# Set NO_GUI to on if using just the console, and no example browser
#option(WITH_GUI "Run the walking model with GUI" OFF)
# Set OPTIMIZATION to on=ASA or off=CMAES
#option(OPTIMIZATION "Set Optimization Technique. on=ASA, off=CMAES" ON)

# configure a header file to pass some of the CMake settings
# to the source code
# configure_file (
#   "${PROJECT_SOURCE_DIR}/Header/GlobalHeader.h.in"
#   "${PROJECT_BINARY_DIR}/GlobalHeader.h"
#   )

#configuration used when GUI is not selected
find_package(OpenCV REQUIRED) #/usr/include/opencv2
find_package(Caffe REQUIRED)

# set(CUDA_DIR "/usr/local/cuda-7.5/targets/x86_64-linux/include/")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
# INCLUDE_DIRECTORIES(${CUDA_DIR})
INCLUDE_DIRECTORIES( "../caffe-ubuntu/include" )
INCLUDE_DIRECTORIES( "./eigen-eigen-67e894c6cd8f" )


# LINK_DIRECTORIES(~/Dropbox/School/Graduate/Simulation_Tests/Caffe/original_caffe/caffe_build/lib/ )
# LINK_LIBRARIES(gtest-d proto-d)

FILE(GLOB SOURCES "*.cpp")
FILE(GLOB HEADERS "*.hpp")
FILE(GLOB HHEADERS "*.h")
# FILE(GLOB HEADERS "Header/*.h" "ASA/*.h")
# LIST(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/Source/GUImain.cpp) #remove the GUImain.cpp file that include GUI


# LINK_DIRECTORIES(
# 	${BULLET_PHYSICS_BUILD_DIR}/src/Bullet3Common
# )


ADD_EXECUTABLE(app_caffe ${SOURCES} ${HEADERS} ${HHEADERS})

target_link_libraries( app_caffe ${OpenCV_LIBS} ${Caffe_LIBRARIES} ) 

	#the following 4 lines are used to include including compiler flags
	#-std=c++11 is to invoke the c++ 11 standard
	#-fopenmp is to enable the OpenMP compiler macros build into the gcc compiler
	#-march=native optimize the code for the local machine
	#-O2 selects the level of optimzation to make
	SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
	add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
	set_property(TARGET app_caffe PROPERTY CXX_STANDARD 11)
	set_property(TARGET app_caffe PROPERTY CXX_STANDARD_REQUIRED ON)
