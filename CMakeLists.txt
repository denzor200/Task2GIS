cmake_minimum_required(VERSION 3.5)

project(Task2GIS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE SRC
    "src/*.cpp"
    "src/*.h"
    )

add_executable(Task2GIS ${SRC})
