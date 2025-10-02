cmake_minimum_required(VERSION 4.0)
project(project2)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        Point.h
        Person.h
        Person.cpp
)
