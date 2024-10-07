cmake_minimum_required(VERSION 3.24)
project(lw_2)

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

add_executable(1_2_3 1_2_3/main.cpp)
add_executable(WeatherObserverTests123 1_2_3/google_test/test.cpp)
target_link_libraries(WeatherObserverTests123 gtest_main gmock)

add_executable(4_5_6 4_5_6/main.cpp)
add_executable(WeatherObserverTests456 4_5_6/google_test/test.cpp)
target_link_libraries(WeatherObserverTests456 gtest_main gmock)

add_executable(7 7/main.cpp)
add_executable(WeatherObserverTests6 7/google_test/test.cpp)
target_link_libraries(WeatherObserverTests6 gtest_main gmock)
