cmake_minimum_required(VERSION 3.30)
project(MyArray)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(MyArray main.cpp
        include/CMyArray.h)

enable_testing()

add_executable(MyArrayTests tests/tests.cpp
        include/CMyArray.h)

target_link_libraries(MyArrayTests gtest)
