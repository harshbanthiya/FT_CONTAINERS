cmake_minimum_required(VERSION 3.24)

set(This Example)
project(${This} C CXX)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
)

set(Sources
    main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
add_subdirectory(tests)