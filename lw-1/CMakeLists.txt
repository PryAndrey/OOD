cmake_minimum_required(VERSION 3.24)
project(lw-1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(GTEST_ENABLE_MOCK ON CACHE BOOL "" FORCE)

add_executable(1 1/main.cpp)
add_executable(DanceTests 1/google_test/test.cpp)
target_link_libraries(DanceTests gtest_main gmock)

add_executable(3 3/main.cpp)

add_executable(4 4/main.cpp 4/models/Canvas/CCanvas.h)
include_directories(4/models/Canvas)

add_executable(graphicTests 4/google_test/test.cpp
        4/models/Canvas/CCanvas.h
        4/models/Canvas/ICanvas.h)
target_link_libraries(graphicTests gtest_main gmock)

target_link_libraries(4 PRIVATE sfml-graphics)
target_compile_features(4 PRIVATE cxx_std_17)