cmake_minimum_required(VERSION 3.15)
project(CaffeBean)

set(CMAKE_CXX_STANDARD 14)

add_executable(CaffeBean main.cpp CaffeBean/src/layer.cpp CaffeBean/include/layer.h CaffeBean/include/net.h CaffeBean/src/net.cpp CaffeBean/include/layers/test_layer.h CaffeBean/src/layers/test_layer.cpp CaffeBean/src/bean.cpp CaffeBean/include/bean.h CaffeBean/include/common.h CaffeBean/include/layers/fully_connected_layer.h CaffeBean/src/layers/fully_connected_layer.cpp)