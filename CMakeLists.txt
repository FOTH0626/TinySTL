cmake_minimum_required(VERSION 3.22)

project(TinySTL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src/allocator)
include_directories(src/algorithm)
include_directories(src/allocator)
include_directories(src/container)
include_directories(src/functor)
include_directories(src/iterator)

add_executable(main main.cpp)

target_compile_options( main PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Werror=return-type
    -Wno-unused-parameter
)

