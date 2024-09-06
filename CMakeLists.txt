cmake_minimum_required(VERSION 3.28)
project(DataStructure_YWM_2nd C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(DataStructure_YWM_2nd
#        main.c
        basic.h
#        chap2/ds/array_list.h
#        chap2/ds/single_linked_list.h
#        chap2/ds/loop_list.h
#        chap2/ds/loop_list.c
#        chap2/ds/loop_list_test.c
#        chap2/leetcode/easy/160-intersection-of-two-linked-lists.c
#        chap2/leetcode/easy/203-remove-linked-list-elements.c
#        chap2/leetcode/easy/206-reverse-linked-list.c
#        chap2/leetcode/easy/234-palindrome-linked-list.c
        chap3/ds/array_stack.h
        chap3/ds/array_stack.c
        chap3/ds/linked_stack.h
        chap3/ds/linked_stack.c
        chap3/ds/array_loop_queue.h
        chap3/ds/array_loop_queue.c
        chap3/ds/linked_queue.h
        chap3/ds/linked_queue.c
        chap5/ds/binary_tree.h
        chap5/ds/binary_tree.c
#        chap5/ds/btree_test.c
        chap5/ds/btnode_stack.h
        chap5/ds/btnode_stack.c
        chap5/ds/btnode.h
        chap5/ds/btnode_queue.h
        chap5/ds/btnode_queue.c
        chap5/ds/huffman_tree.h
        chap5/ds/huffman_tree.c
#        chap5/ds/huffman_tree_test.c
#        chap5/leetcode/easy/94-binary-tree-inorder-traversal.c
#        chap5/leetcode/easy/100-same-tree.c
#        chap5/leetcode/easy/101-symmetric-tree.c
#        chap5/leetcode/easy/104-maximum-depth-of-binary-tree.c
        chap6/ds/adjacency_matrix_graph.h
#        chap6/ds/adjacency_matrix_graph_test.c
        chap6/ds/adjacency_matrix_graph.c
        chap6/ds/adjacency_list_graph.h
        chap6/ds/adjacency_list_graph.c
#        chap6/ds/adjacency_list_graph_test.c
        chap6/ds/orthogonal_list_graph.h
        chap6/ds/orthogonal_list_graph.c
#        chap6/ds/orthogonal_list_graph_test.c
        chap6/ds/adjacency_multi_list_graph.h
        chap6/ds/adjacency_multi_list_graph.c
#        chap7/ds/sequence_table_search.c
        chap7/ds/binary_search_tree.c
        #        chap6/ds/adjacency_multi_list_graph_test.c
        #        "chap3/example/3.1 base_convert.c"
#        "chap3/example/3.2 bracket_match.c"
#        "chap3/example/3.3 calculate_expression.c"
#        "chap3/example/3.4 dancing partner.c"
#        "chap3/exercise/algo design/1-double_stack_in_one_array.c"
#        "chap3/exercise/algo design/2-palindrome-stack-judge.c"
#        "chap3/exercise/algo design/4-postfix_expression_calc.c"
#        "chap3/exercise/algo design/3-integer_stack.c"
#        "chap3/exercise/algo design/5-stack_io_legal_ascertain.c"
#        chap3/exp/240.c
#        chap3/exp/247.c
#        "chap4/example/4.1 virus_detect.c"
#        chap4/exp/256.c
#        chap4/exp/257.c
#        chap4/exp/258.c
#        chap4/exp/259.c
#        chap4/exp/260.c
        #        chap2/ds/two_direct_list.h
#        chap2/ds/array_list.c
#        chap2/array_list_merge.c
#        chap2/ds/single_linked_list.c
#        chap2/exp/216.c
#        chap2/exp/217.c
#        chap2/exp/218.c
#        chap2/exp/219.c
#        chap2/exp/220.c
#        chap2/exp/221.c
#        chap2/exp/222.c
#        chap2/exp/223.c
#        chap2/leetcode/easy/21-merge-two-sorted-lists.c
#        chap2/leetcode/easy/83-remove-duplicates-from-sorted-list.c
#        chap2/leetcode/easy/141-linked-list-cycle.c
        #        chap2/example/2.1_array_unary_poly.c
#        chap2/example/2.2_sparse_poly.c
#        chap2/exp/arr_book.c
#        chap2/exp/linked_list_tmpl.c
#        chap2/exp/214.c
#        chap2/exp/215.c
        #        chap2/single_linked_list_merge.c
        #        chap2/single_linked_list_test.c
)

