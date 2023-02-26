cmake_minimum_required(VERSION 3.11...3.25)

project(ascii_art_gen
    VERSION 1.0
    DESCRIPTION "ASCII Art Generator"
)

set(AAG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include"
    CACHE STRING "${PROJECT_NAME} include directory.")
set(AAG_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"
    CACHE STRING "${PROJECT_NAME} binary directory.")

add_compile_options(
    -Wall
    -Wextra
    -pedantic
    -Werror
    -Wno-sign-compare
    -std=c++17
    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

add_subdirectory(src)
add_subdirectory(ascii_art_gen)
