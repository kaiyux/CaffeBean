cmake_minimum_required(VERSION 3.15)
project(CaffeBean)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(CaffeBean/src SRC_LIST)
aux_source_directory(CaffeBean/src/layers LAYERS_LIST)
aux_source_directory(3rdparty/jsoncpp/src/lib_json JSON_LIBS)

find_package(Boost REQUIRED)

SET(CAFFEBEAN_INCLUDE_DIRS CaffeBean/include)
SET(EIGEN_PATH 3rdparty/Eigen)
SET(JSONCPP_INCLUDE_DIRS 3rdparty/jsoncpp/include)
SET(JPEG_INCLUDE_DIRS /Users/kaiyu/workspace/image-libraries/jpeg-9d/build/include)
include_directories(${CAFFEBEAN_INCLUDE_DIRS} ${EIGEN_PATH} ${JSONCPP_INCLUDE_DIRS} ${JPEG_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

SET(JPEG_LIBRARY_DIRS /Users/kaiyu/workspace/image-libraries/jpeg-9d/build/lib)
link_directories(${JPEG_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

add_executable(CaffeBean main.cpp ${LAYERS_LIST} ${SRC_LIST} ${JSON_LIBS})

target_link_libraries(CaffeBean jpeg)
add_subdirectory(3rdparty)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(CaffeBean PUBLIC DEBUG=1)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(CaffeBean PUBLIC DEBUG=0)
endif ()