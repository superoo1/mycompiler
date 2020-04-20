cmake_minimum_required(VERSION 3.15)
project(untitled3 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled3 main.c mylang.h MEM.h DBG.h InterP.h create.c util.c string.c testutil/tset1.c)