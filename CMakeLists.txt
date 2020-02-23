cmake_minimum_required(VERSION 3.15)
project(CaffeBean)

set(CMAKE_CXX_STANDARD 14)

include_directories(CaffeBean/include)
aux_source_directory(CaffeBean/src SRC_LIST)
aux_source_directory(CaffeBean/src/layers LAYERS_LIST)

include_directories(lib/jsoncpp/include)
aux_source_directory(lib/jsoncpp/src/lib_json JSON_LIBS)

add_executable(CaffeBean main.cpp ${LAYERS_LIST} ${SRC_LIST} ${JSON_LIBS})

add_subdirectory(lib)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(CaffeBean PUBLIC DEBUG=1)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(CaffeBean PUBLIC DEBUG=0)
endif ()