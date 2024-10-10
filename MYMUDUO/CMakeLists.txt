cmake_minimum_required(VERSION 2.5)
project(mymuduo)

# 编程 so 放到 lib
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11") # 可debug

aux_source_directory(. SRC_LIST)
# so
add_library(mymuduo SHARED ${SRC_LIST})
