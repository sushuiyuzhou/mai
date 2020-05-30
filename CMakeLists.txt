cmake_minimum_required(VERSION 3.12)
project(mai)

set(CMAKE_CXX_STANDARD 17)

add_executable(mai
               main.cpp
               lib/Context.cpp
               lib/Node.cpp
               lib/Graph.cpp)