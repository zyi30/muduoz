cmake_minimum_required(VERSION 3.28.3)
project(mymuduo)
#MYMUDUO最终编译成so动态库，设置动态库的路径，放在根目录lib
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#设置调试信息,启动C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11  -FPIC")
#定义参与编译的源代码文件
aux_source_directory(. SRC_LIST)
#编译生成动态库
add_library(mymuduo SHARED ${SRC_LIST})