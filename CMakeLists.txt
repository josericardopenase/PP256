cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled
        sha256.h
        hexutils.c
        hexutils.h
        main.c
        sha256.c
        encrypt.h
)
