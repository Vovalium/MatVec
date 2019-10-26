cmake_minimum_required(VERSION 3.13)
project(C__)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(--coverage)
link_libraries(gcov)

include_directories(.)

add_executable(C__
        Base.h
        Main.cpp
        Matrix.cpp
        Matrix.h
        Vector.h
        Vector.cpp
        Catch.hpp)