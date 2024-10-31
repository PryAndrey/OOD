cmake_minimum_required(VERSION 3.24)
project(lw_6)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательный стандарт
set(CMAKE_CXX_EXTENSIONS OFF)         # Без расширений компилятора

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

set(SOURCE_FILES1
        1/Libs/graphics_lib.h
        1/Libs/modern_graphics_lib.h
        1/Libs/shape_drawing_lib.h
        1/ModernGraphicsAdapter.h
)
set(SOURCE_FILES2
        2/Libs/graphics_lib.h
        2/Libs/modern_graphics_lib.h
        2/Libs/shape_drawing_lib.h
        2/ModernGraphicsClassAdapter.h
)
set(SOURCE_FILES2
        3/Libs/graphics_lib.h
        3/Libs/modern_graphics_lib.h
        3/Libs/shape_drawing_lib.h
        3/ModernGraphicsClassAdapter.h
)

add_executable(1 1/main.cpp ${SOURCE_FILES1})
add_executable(1_test 1/tests/test.cpp ${SOURCE_FILES1})
target_link_libraries(1_test gtest_main gmock gtest)

add_executable(2 2/main.cpp ${SOURCE_FILES2})
add_executable(2_test 2/tests/test.cpp ${SOURCE_FILES2})
target_link_libraries(2_test gtest_main gmock gtest)

add_executable(3 3/main.cpp ${SOURCE_FILES3})
add_executable(3_test 3/tests/test.cpp ${SOURCE_FILES3})
target_link_libraries(3_test gtest_main gmock gtest)


