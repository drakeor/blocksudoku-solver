cmake_minimum_required(VERSION 3.5)

project(bssolver VERSION 1.0)

include_directories("${PROJECT_SOURCE_DIR}/eigen")

add_executable(bssolver main.cpp blockfactory.cpp)
add_executable(tests_bssolver main_test.cpp catch.cpp blockfactory.cpp)