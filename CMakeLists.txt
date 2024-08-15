cmake_minimum_required(VERSION 3.28)
project(DataStructure_YWM_2nd C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(DataStructure_YWM_2nd
#        main.c
        basic.h
        chap2/ds/array_list.h
        chap2/ds/single_linked_list.h
        chap2/ds/loop_list.h
        chap2/ds/two_direct_list.h
        chap2/ds/array_list.c
#        chap2/array_list_merge.c
        chap2/ds/single_linked_list.c
#        chap2/exp/216.c
#        chap2/exp/217.c
#        chap2/exp/218.c
#        chap2/exp/219.c
#        chap2/exp/220.c
#        chap2/exp/221.c
#        chap2/exp/222.c
        chap2/exp/223.c
        chap2/leetcode/easy/21-merge-two-sorted-lists.c
        chap2/leetcode/easy/remove-duplicates-from-sorted-list.c
        #        chap2/example/2.1_array_unary_poly.c
#        chap2/example/2.2_sparse_poly.c
#        chap2/exp/arr_book.c
#        chap2/exp/linked_list_tmpl.c
#        chap2/exp/214.c
#        chap2/exp/215.c
        #        chap2/single_linked_list_merge.c
        #        chap2/single_linked_list_test.c
)

