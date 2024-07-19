cmake_minimum_required(VERSION 3.0.0)
project(tankwar VERSION 0.1.0)

add_compile_options(-O2 -Werror -Wall -Wextra -Wpedantic -std=c++1z)

add_executable(tankwar tankwar.cpp gameProcess.cpp gameProcess.h gameControl.cpp gameControl.h tankai.cpp tankai.h)
