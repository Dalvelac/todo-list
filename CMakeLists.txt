cmake_minimum_required(VERSION 3.29)
project(todo_list)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(todo_list
    todo.cpp
        main.cpp
)
