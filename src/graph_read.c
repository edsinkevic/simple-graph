//
// Created by edvin on 23.2.27.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_read.h"


void interpret_line(graph_t graph, char *buffer);

graph_t graph_read(char *filename) {
    int buffer_length = 255;
    char *buffer = calloc(buffer_length, sizeof *buffer);

    FILE *file_handle = fopen(filename, "r");

    graph_t graph = graph_create(0);

    while (fgets(buffer, buffer_length, file_handle) != NULL) {
        interpret_line(graph, buffer);
    }

    fclose(file_handle);
    free(buffer);

    return graph;
}

void interpret_line(graph_t graph, char *buffer) {
    char *end_ptr;
    char *save_ptr;
    char *token;
    int digit_base = 10;

    token = strtok_r(buffer, " -> ", &save_ptr);
    unsigned long vertex = strtoul(token, &end_ptr, digit_base);
    graph_increase_size(graph, vertex + 1);

    token = strtok_r(NULL, " -> ", &save_ptr);
    while (token != NULL) {
        unsigned int edge_vertex = strtoul(token, &end_ptr, digit_base);
        graph_increase_size(graph, edge_vertex + 1);
        graph_add_edge(graph, vertex, edge_vertex);
        token = strtok_r(NULL, " -> ", &save_ptr);
    }
}
