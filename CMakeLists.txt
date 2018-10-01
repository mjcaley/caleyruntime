cmake_minimum_required (VERSION 3.8)

project (caleyruntime)

set (CMAKE_C_STANDARD 11)

add_library (caleyruntime STATIC src/gc.c)
target_include_directories (caleyruntime PUBLIC include)

set (CALEYRUNTIME_INCLUDE include)

add_subdirectory (demo)
