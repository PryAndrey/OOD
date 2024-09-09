cmake_minimum_required(VERSION 3.24)
project(lw-1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(1 1/main.cpp)

add_executable(3 3/main.cpp)

add_executable(4 4/main.cpp 4/CShapeService.cpp)
add_executable(graphicTests 4/google_test/test.cpp 4/CShapeService.cpp 4/google_test/mock/CShapeServiceMock.cpp)
target_link_libraries(graphicTests gtest_main)

