cmake_minimum_required(VERSION 3.26)
project(P97_CLI)

set(CMAKE_CXX_STANDARD 23)

add_executable(P97_CLI main.cpp
        P97-FMAN.h)
