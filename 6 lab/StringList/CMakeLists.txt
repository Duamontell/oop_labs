cmake_minimum_required(VERSION 3.30)
project(StringList)

set(CMAKE_CXX_STANDARD 20)

add_executable(StringList main.cpp
        src/CStringList.cpp
        include/CStringList.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(StringListTests tests/tests.cpp
        src/CStringList.cpp
        include/CStringList.h)

target_link_libraries(StringListTests gtest gtest_main)