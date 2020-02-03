cmake_minimum_required(VERSION 3.15)
project(CaffeBeanWithTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(CaffeBean/include)
aux_source_directory(CaffeBean/src SRC_LIST)
aux_source_directory(CaffeBean/src/layers LAYERS_LIST)

add_executable(CaffeBean main.cpp ${LAYERS_LIST} ${SRC_LIST})

add_subdirectory(lib)