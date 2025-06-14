cmake_minimum_required(VERSION 3.30)
project(MyString)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyString main.cpp
        src/CMyString.cpp
        include/CMyString.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестирования
enable_testing()

add_executable(MyStringTests tests/tests.cpp
        src/CMyString.cpp
        include/CMyString.h)

# Линкуем тесты с GoogleTest и GoogleTest Main.
target_link_libraries(MyStringTests PRIVATE gtest gtest_main)

# Регистрируем тестовую цель в CTest.
add_test(NAME MyStringTests COMMAND MyStringTests)
