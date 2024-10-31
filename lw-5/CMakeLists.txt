cmake_minimum_required(VERSION 3.24)
project(lw_5)

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

set(SOURCE_FILES
        1/models/Menu/Menu.cpp
        1/models/Commands/CCommand/CCommand.cpp
        1/models/commands/DeleteItemCommand/DeleteItemCommand.cpp
        1/models/commands/InsertImageCommand/InsertImageCommand.cpp
        1/models/commands/InsertParagraphCommand/InsertParagraphCommand.cpp
        1/models/commands/ReplaceTextCommand/ReplaceTextCommand.cpp
        1/models/commands/ResizeImageCommand/ResizeImageCommand.cpp
        1/models/commands/SetTitleCommand/SetTitleCommand.cpp
        1/models/commands/SaveCommand/SaveCommand.cpp
        1/models/Document/Elements/Paragraph.cpp
        1/models/Document/Elements/Image.cpp
        1/models/Document/Document.cpp
        1/models/Document/Items/ConstDocumentItem.cpp
        1/models/Document/Items/DocumentItem.cpp
        1/models/Document/History/History.cpp)

add_executable(1 1/main.cpp ${SOURCE_FILES})

add_executable(1_test 1/tests/tests.cpp ${SOURCE_FILES})
target_link_libraries(1_test gtest_main gmock gtest)
enable_testing()
add_test(NAME 1_test COMMAND 1_test)
