cmake_minimum_required(VERSION 3.16)

project(
    aoc2024
    VERSION 0.0.1
    DESCRIPTION "Advent of Code - 2024"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true) # for the lsp
set(CMAKE_COMPILE_WARNING_AS_ERROR true)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup
    INTERFACE -Wall -Wpedantic -Wextra -Werror)
target_compile_features(cxx_setup INTERFACE cxx_std_20)
target_include_directories(cxx_setup INTERFACE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
