cmake_minimum_required(VERSION 3.5)

project(bssolver VERSION 1.0)


include_directories("${PROJECT_SOURCE_DIR}/eigen")

list(APPEND srclist "blockfactory.cpp" "blocksudoku.cpp" "game.cpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++17 -fopenmp -O3")

add_executable(bssolver main.cpp ${srclist})
add_executable(tests_bssolver main_test.cpp catch.cpp blockfactory_tests.cpp blocksudoku_test.cpp game_test.cpp ${srclist})