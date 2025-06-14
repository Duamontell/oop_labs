cmake_minimum_required(VERSION 3.30)
project(HTTP_URL)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(HTTP_URL main.cpp)

enable_testing()

add_executable(tests tests/tests.cpp)

add_library(HTTP_URL_lib STATIC HttpUrl_lib.cpp HttpUrl_lib.h
        src/CHttpUrl.cpp
        include/CHttpUrl.h
        src/CUrlParsingError.cpp
        include/CUrlParsingError.h)

target_include_directories(HTTP_URL_lib PUBLIC include)

target_link_libraries(HTTP_URL PRIVATE HTTP_URL_lib)
target_link_libraries(tests PRIVATE gtest gtest_main)
target_link_libraries(tests LINK_PUBLIC HTTP_URL_lib)

add_test(NAME HttpUrlTests COMMAND HttpUrlTests)