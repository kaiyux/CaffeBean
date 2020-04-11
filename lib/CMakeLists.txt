# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest)
include_directories(./googletest/include ./googletest)

# 'Google_Tests_run' is the target name
# 'tests.cpp' are source files with tests
include_directories(../CaffeBean/include)
aux_source_directory(../CaffeBean/src/ SRC_LIST_FOR_TEST)
aux_source_directory(../CaffeBean/src/layers LAYERS_LIST_FOR_TEST)

include_directories(./jsoncpp/include)
aux_source_directory(./jsoncpp/src/lib_json JSON_LIBS__FOR_TEST)

include_directories(/Users/kaiyu/GitHub/boost_1_72_0/build/include)
link_directories(/Users/kaiyu/GitHub/boost_1_72_0/build/lib)

include_directories(/Users/kaiyu/workspace/image-libraries/jpeg-9d/build/include)
link_directories(/Users/kaiyu/workspace/image-libraries/jpeg-9d/build/lib)

add_executable(Google_Tests_run ./tests.cpp ${SRC_LIST_FOR_TEST} ${LAYERS_LIST_FOR_TEST} ${JSON_LIBS__FOR_TEST})
target_link_libraries(Google_Tests_run jpeg)
target_link_libraries(Google_Tests_run gtest gtest_main)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Google_Tests_run PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Google_Tests_run PUBLIC DEBUG=0)
endif()