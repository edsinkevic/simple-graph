//
// Created by edvin on 23.2.26.
//

#include <stddef.h>
#include "graph_generate.h"
#include <stdio.h>

unsigned int calculate_max_edge_count(unsigned int n);

unsigned int random_uint(unsigned int limit, FILE *dev_random_file_handle);

unsigned int random_number_between(unsigned int from, unsigned int to, FILE *dev_random_file_handle);

int args_not_valid(unsigned int vertex_amount, unsigned int neighbor_min, unsigned int neighbor_max);

void fill_vertex(graph_t graph, unsigned int vertex_index, unsigned int neighbor_min, unsigned int neighbor_max,
                 FILE *dev_random_file_handle);

graph_t graph_generate(unsigned int vertex_amount, unsigned int neighbor_min, unsigned int neighbor_max) {
    if (args_not_valid(vertex_amount, neighbor_min, neighbor_max))
        return NULL;

    graph_t graph = graph_create(vertex_amount);

    FILE *f = fopen("/dev/random", "r");

    for (unsigned int i = 0; i < vertex_amount; i++) {
        fill_vertex(graph, i, neighbor_min, neighbor_max, f);
    }

    fclose(f);

    return graph;
}

void fill_vertex(graph_t graph, unsigned int vertex_index, unsigned int neighbor_min, unsigned int neighbor_max,
                 FILE *dev_random_file_handle) {
    unsigned int random_neighbor_count = random_number_between(neighbor_min, neighbor_max, dev_random_file_handle);
    unsigned int vertex_count = graph_get_vertex_count(graph);
    unsigned int last_vertex_index = vertex_count - 1;
    unsigned int random_neighbor_vertex;

    for (unsigned int i = 0; i < random_neighbor_count; i++) {
        do {
            random_neighbor_vertex = random_number_between(0, last_vertex_index, dev_random_file_handle);
            if (random_neighbor_vertex == vertex_index)
                random_neighbor_vertex = vertex_index + 1 < vertex_count ? vertex_index + 1 : vertex_index - 1;
        } while (graph_edge_exists(graph, vertex_index, random_neighbor_vertex));

        graph_add_edge(graph, vertex_index, random_neighbor_vertex);
    }
}

int args_not_valid(unsigned int vertex_amount, unsigned int neighbor_min, unsigned int neighbor_max) {
    if (neighbor_max >= vertex_amount)
        return 1;

    if (neighbor_min >= vertex_amount)
        return 1;

    if (neighbor_min > neighbor_max)
        return 1;

    unsigned int max_edge_count = calculate_max_edge_count(vertex_amount);
    if (max_edge_count < neighbor_min * vertex_amount)
        return 1;

    return 0;
}


unsigned int calculate_max_edge_count(unsigned int n) {
    return n * (n - 1);
}


unsigned int random_uint(unsigned int limit, FILE *dev_random_file_handle) {
    unsigned int random_number;
    fread(&random_number, sizeof random_number, 1, dev_random_file_handle);
    return random_number % (limit + 1);
}

unsigned int random_number_between(unsigned int from, unsigned int to, FILE *dev_random_file_handle) {
    if (from > to) {
        unsigned int temp = to;
        to = from;
        from = temp;
    }

    unsigned int length = to - from;

    return from + (random_uint(length, dev_random_file_handle));
}