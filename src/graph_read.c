//
// Created by edvin on 23.2.27.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_read.h"


inline void interpret_line(graph_t graph, char *buffer);

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
    char *from;
    char *to;
    int digit_base = 10;

    from = strtok_r(buffer, " ", &save_ptr);
    unsigned long vertex_from = strtoul(from, &end_ptr, digit_base);

    graph_increase_size(graph, vertex_from + 1);

    to = strtok_r(NULL, " ", &save_ptr);

    if (to != NULL) {
        unsigned int vertex_to = strtoul(to, &end_ptr, digit_base);
        graph_add_edge(graph, vertex_from, vertex_to);
    }
}
