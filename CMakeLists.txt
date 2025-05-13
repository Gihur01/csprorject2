cmake_minimum_required(VERSION 3.29)
project(Library-management)

set(CMAKE_CXX_STANDARD 20)

add_executable(Library-management main.cpp
        Item.cpp
        Item.h
        User.cpp
        User.h
        Record.cpp
        Record.h
)
