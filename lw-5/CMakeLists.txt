cmake_minimum_required(VERSION 3.24)
project(lw_5)

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

add_executable(lw_5 main.cpp)

#add_executable(1 1/main.cpp
#        1/models/Picture/CPicture.cpp
#        1/models/Shapes/Triangle/CTriangle.cpp
#        1/models/Shapes/Rectangle/CRectangle.cpp
#        1/models/Shapes/Polygon/CPolygon.cpp
#        1/models/Shapes/Ellipse/CEllipse.cpp
#        1/models/Shapes/CShape.cpp
#        1/models/CShapeFactory.cpp
#        1/models/Designer/CDesigner.cpp)
#
#add_executable(1_2_3 1_2_3/main.cpp)
#add_executable(WeatherObserverTests123 1_2_3/google_test/test.cpp)
#target_link_libraries(WeatherObserverTests123 gtest_main gmock)