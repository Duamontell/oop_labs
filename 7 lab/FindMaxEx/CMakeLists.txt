cmake_minimum_required(VERSION 3.30)
project(FindMaxEx)

set(CMAKE_CXX_STANDARD 20)

add_executable(FindMaxEx main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/tests.cpp)

enable_testing()

target_link_libraries(tests PRIVATE gtest)