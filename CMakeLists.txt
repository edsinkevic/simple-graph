cmake_minimum_required(VERSION 3.24)
project(lab_1 C)

set(CMAKE_C_STANDARD 23)

include_directories(src)

add_executable(lab_1 src/main.c src/graph.c src/graph.h src/graph_generate.c src/graph_generate.h src/linked_list.c src/linked_list.h src/graph_read.c src/graph_read.h src/graph_dfs.c src/graph_dfs.h src/stack.c src/stack.h src/tests/test_graph.c src/tests/test_graph.h src/tests/test_linked_list.c src/tests/test_linked_list.h src/tests/test_graph_generate.c src/tests/test_graph_generate.h src/tests/test_graph_read.c src/tests/test_graph_read.h src/tests/test_stack.c src/tests/test_stack.h src/tests/test_graph_dfs.c src/tests/test_graph_dfs.h)
