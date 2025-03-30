cmake_minimum_required(VERSION 3.30)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(Calculator main.cpp
        src/Calculator.cpp
        include/Calculator.h
        src/Variable.cpp
        include/Variable.h
        src/Function.cpp
        include/Function.h
        src/Expression.cpp
        include/Expression.h
)

include_directories(include)

add_executable(tests
        tests/tests.cpp
        include/Calculator.h
        src/Calculator.cpp
        include/Variable.h
        src/Variable.cpp
        src/Function.cpp
        include/Function.h
        src/Expression.cpp
        include/Expression.h
)

target_link_libraries(tests gtest)