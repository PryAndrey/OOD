cmake_minimum_required(VERSION 3.24)
project(lw_4)

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

add_executable(1 1/main.cpp
        1/models/Picture/CPicture.cpp
        1/models/Shapes/Triangle/CTriangle.cpp
        1/models/Shapes/Rectangle/CRectangle.cpp
        1/models/Shapes/Polygon/CPolygon.cpp
        1/models/Shapes/Ellipse/CEllipse.cpp
        1/models/Shapes/CShape.cpp
        1/models/CShapeFactory.cpp
        1/models/Designer/CDesigner.cpp)

enable_testing()

add_executable(factoryTests
        1/google_test/main.cpp
        1/google_test/shapeFactoryTest.cpp
        1/models/Picture/CPicture.cpp
        1/models/Shapes/Triangle/CTriangle.cpp
        1/models/Shapes/Rectangle/CRectangle.cpp
        1/models/Shapes/Polygon/CPolygon.cpp
        1/models/Shapes/Ellipse/CEllipse.cpp
        1/models/Shapes/CShape.cpp
        1/models/CShapeFactory.cpp
        1/models/Designer/CDesigner.cpp
        1/google_test/clientTest.cpp
        1/google_test/designerTest.cpp
        1/google_test/painterTest.cpp
        1/google_test/shapeTest.cpp 1/google_test/pictureTest.cpp)

target_link_libraries(factoryTests GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(factoryTests)
