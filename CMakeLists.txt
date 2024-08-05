cmake_minimum_required(VERSION 3.28)
project(DataStructure_YWM_2nd C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(DataStructure_YWM_2nd main.c
        basic.h
        chap2/list.h)
