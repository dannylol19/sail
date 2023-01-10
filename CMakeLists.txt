cmake_minimum_required(VERSION 3.24)
project(sail_vm)

set(CMAKE_CXX_STANDARD 23)

add_executable(sail_vm main.cpp flags.h opcodes.h registers.h vm.h vm.cpp)
