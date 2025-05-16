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
        Modules.cpp
        Modules.h
        Modules.h
        InputHelpers.cpp
        InputHelpers.h
        Printer.cpp
        Printer.h
        DynArr.cpp
        DynArr.h
)
