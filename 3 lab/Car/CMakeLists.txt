cmake_minimum_required(VERSION 3.30)
project(Car)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(GoogleTest/lib)

add_executable(Car main.cpp
        source/Car.cpp
        include/Car.h
        source/Engine.cpp
        include/Engine.h
        source/Transmission.cpp
        include/Transmission.h
        include/Constants.h
        source/CarController.cpp
        include/CarController.h)

include_directories(include)

add_executable(tests
        tests/test.cpp
        source/CarController.cpp
        include/CarController.h
        source/Car.cpp
        include/Car.h
        source/Engine.cpp
        include/Engine.h
        source/Transmission.cpp
        include/Transmission.h
        include/Constants.h
)

target_link_libraries(tests gtest)

