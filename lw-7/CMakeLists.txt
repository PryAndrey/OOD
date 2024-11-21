cmake_minimum_required(VERSION 3.26)
project(lw_7)

set(CMAKE_CXX_STANDARD 20)

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
#set
set(GTEST_ENABLE_MOCK ON CACHE BOOL "" FORCE)

set(SOURCE_FILES
        1/models/main.cpp
        1/models/Client.h
        1/models/Shape/Factory/IShapeFactory.h
        1/models/Shape/Factory/ShapeFactory.h
        1/models/Shape/SimpleShapes/Triangle.h
        1/models/Shape/SimpleShapes/Rectangle.h
        1/models/Shape/SimpleShapes/Ellipse.h
        1/models/Shape/SimpleShapes/Shape.h
        1/models/Shape/Styles/IStyle.h
        1/models/Shape/IShape.h
        1/models/IDrawable.h
        1/models/Shape/GroupShape.h
        1/models/Shape/IGroupShape.h
        1/models/Slide/ISlide.h
        1/models/Slide/Slide.h
        1/models/Slide/SlideService.h
        1/models/CoreTypes.h
        1/models/Shape/Styles/LineStyle/GroupLineStyle.h
        1/models/Canvas/SVGCanvas.h
        1/models/Shape/Styles/LineStyle/ILineStyle.h
        1/models/Shape/Styles/LineStyle/SimpleLineStyle.h
        1/models/Shape/Styles/FillStyle/SimpleFillStyle.h
        1/models/Shape/Styles/FillStyle/IFillStyle.h
        1/models/Shape/Styles/FillStyle/GroupFillStyle.h
        1/models/Shape/Styles/StyleEnumerator.h

)

set(TEST_SOURCE_FILES test/test.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
#target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)