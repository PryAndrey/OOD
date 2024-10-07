cmake_minimum_required(VERSION 3.24)
project(lw_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(GTEST_ENABLE_MOCK ON CACHE BOOL "" FORCE)

add_executable(3 3/main.cpp)
#add_executable(BeverageTests12 1_2/google_test/test.cpp)
#target_link_libraries(BeverageTests12 gtest_main gmock)

