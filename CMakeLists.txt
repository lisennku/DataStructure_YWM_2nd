cmake_minimum_required(VERSION 3.28)
project(DataStructure_YWM_2nd C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(DataStructure_YWM_2nd
#        main.c
        basic.h
        chap2/array_list.h
        chap2/single_linked_list.h
        chap2/loop_list.h
        chap2/two_direct_list.h
        chap2/array_list.c
#        chap2/array_list_merge.c
        chap2/single_linked_list.c
        chap2/example/2.1_array_unary_poly.c
        #        chap2/single_linked_list_merge.c
        #        chap2/single_linked_list_test.c
)

