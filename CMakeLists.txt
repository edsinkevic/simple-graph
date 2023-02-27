cmake_minimum_required(VERSION 3.24)
project(lab_1 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab_1 main.c graph.c graph.h generate.c generate.h graph_node.c graph_node.h graph_read.c graph_read.h)
