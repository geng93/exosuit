This program uses CAFFE neural network library from http://caffe.berkeleyvision.org/
It has official ubuntu support, with Windows unofficial support. However, the windows version keeps failing to build properly.
This instruction is for building Caffe in "Windows Subsystem for Linux" in Windows 10


Caffe Installation
-------------------
1) Install ubuntu distribution for WSL. Follow the document "Install the Linux Subsystem on Windows 10 _ Microsoft Docs.pdf" 
2) The installed ubuntu should be 16.04 LTS as of 26-Mar-2018
3) Next, follow the following instructions to install all appropriate libraries for ubuntu. It is the same instructions as listed in http://caffe.berkeleyvision.org/install_apt.html for ubuntu<17.04

in Ubuntu
4) sudo apt-get update
5) sudo apt-get upgrade
6) sudo apt-get install build-essential cmake libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
7) sudo apt-get install --no-install-recommends libboost-all-dev
8) sudo apt-get install libopenblas-dev
9) echo "export OPENBLAS_NUM_THREADS=4\nexport GOTO_NUM_THREADS=4\nexport OMP_NUM_THREADS=4" >> ~/.bash_profile 
    - NUM_THREADS=4 is because the number of threads in my computer is 4. If yours have more threads, change the number

in Windows
10) go to https://github.com/BVLC/caffe and download the latest source code in a zip format
11) save it to a location, for example "C:/Users/JieKai/Documents/Exosuit"
12) unzip the file and take note of the folder name (should be "caffe-main")
13) change that folder name from "caffe-main" to "caffe-ubuntu"
    - Must change, if not we need to change the CMakeLists.txt file, which is more complicated
14) copy the "build.sh" file from Installation_Instructions folder to caffe-ubuntu folder

in Ubuntu
13) cd /mnt/c/Users/JieKai/Documents/Exosuit/caffe-ubuntu
14) ./build.sh
15) Caffe should build properly without problems. If you meet a problem about hdf5, follow the segment "HDF5 cmake problem"
16) else, go to the next segment "Exosuit Compliancy Code Compilation" to build the neural network code


Exosuit Compliancy Code Compilation
----------------------------------
1) Make sure this entire main folder "exosuit" is located beside the "caffe-ubuntu" folder
In Ubuntu
2) cd /mnt/c/Users/JieKai/Documents/Exosuit/exosuit
3) ./build.sh
4) ./build/app_caffe  (This should run the neural network program)



HDF5 cmake problem
--------------------
1) When installing hdf5 through "sudo apt-get install libhdf5-serial-dev", the find_hdf5.cmake file is not created. The latest version of hdf5 remove that cmake file generation capability
2) Solution is to tell Caffe's cmake where to find hdf5.
In Windows
3) go to caffe-ubuntu > cmake > Dependencies.cmake
4) Comment the following lines by adding # in front:
		# find_package(HDF5 COMPONENTS HL REQUIRED)
		# MESSAGE(${HDF5_INCLUDE_DIRS})
		# list(APPEND Caffe_INCLUDE_DIRS PUBLIC ${HDF5_INCLUDE_DIRS})
        # list(APPEND Caffe_LINKER_LIBS PUBLIC ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
5) Add in the following lines:
		list(APPEND Caffe_INCLUDE_DIRS PUBLIC "/usr/lib/x86_64-linux-gnu/hdf5/serial/include")
        list(APPEND Caffe_LINKER_LIBS PUBLIC "/usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5.so" "/usr/lib/x86_64-linux-gnu/hdf5/serial/lib/libhdf5_hl.so")
In Ubuntu
6) go inside caffe-ubuntu folder and rerun "./build.sh"