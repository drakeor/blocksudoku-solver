cmake_minimum_required(VERSION 3.21)

project(bssolver VERSION 1.0)

# Global output/config toggles
# Use per-configuration output directories for multi-config generators
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")
endif()

# Detect if OpenMP is available, if not, disable related code
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "Found OpenMP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    add_definitions(-DHAVE_OPENMP)
else()
    message(STATUS "OpenMP not found, proceeding without it")
endif()

find_package(Catch2 CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

# Include Catch2 module for test discovery
include(CTest)
include(Catch)

list(APPEND srclist "src/blockfactory.cpp" "src/blocksudoku.cpp" "src/game.cpp")

add_executable(bssolver src/main.cpp ${srclist})
target_include_directories(bssolver PUBLIC include)
target_link_libraries(bssolver PRIVATE Eigen3::Eigen)
add_executable(tests_bssolver tests/main_test.cpp tests/blockfactory_tests.cpp tests/blocksudoku_test.cpp tests/game_test.cpp ${srclist})
target_include_directories(tests_bssolver PUBLIC include)
target_link_libraries(tests_bssolver PRIVATE Catch2::Catch2WithMain Eigen3::Eigen)
catch_discover_tests(tests_bssolver
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    PROPERTIES LABELS "unit"
)
install(TARGETS bssolver DESTINATION bin)