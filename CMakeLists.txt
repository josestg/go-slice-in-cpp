cmake_minimum_required(VERSION 3.26)
project(go_slice_in_cpp)

set(CMAKE_CXX_STANDARD 17)

## Setup GoogleTest as unit testing framework.
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


add_library(go_slice_in_cpp_lib slice.cpp slice.h)
add_executable(go_slice_in_cpp_demo main.cpp)
add_executable(go_slice_in_cpp_test slice_test.cpp)

target_link_libraries(go_slice_in_cpp_demo go_slice_in_cpp_lib)

target_link_libraries(
        go_slice_in_cpp_test
        go_slice_in_cpp_lib
        gtest_main
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(go_slice_in_cpp_test)