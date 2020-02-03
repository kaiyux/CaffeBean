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
#MESSAGE( STATUS "this var key = ${SRC_LIST_FOR_TEST}.")
#MESSAGE( STATUS "this var key = ${LAYERS_LIST_FOR_TEST}.")

add_executable(Google_Tests_run ./tests.cpp ${SRC_LIST_FOR_TEST} ${LAYERS_LIST_FOR_TEST})
target_link_libraries(Google_Tests_run gtest gtest_main)