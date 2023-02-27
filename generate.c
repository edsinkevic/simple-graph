//
// Created by edvin on 23.2.26.
//

#include <stddef.h>
#include "generate.h"
#include <stdio.h>

unsigned int calculate_max_edge_count(unsigned int n);

unsigned int random_uint(unsigned int limit);

unsigned int random_number_between(unsigned int from, unsigned int to);

unsigned int min(unsigned int first, unsigned int second);

unsigned int max(unsigned int first, unsigned int second);

int args_not_valid(unsigned int vertex_amount, unsigned int neighbor_min, unsigned int neighbor_max);

void fill_vertex_lacking_neighbors(graph_t graph, unsigned int lacking, unsigned int neighbor_min,
                                   unsigned int neighbor_max);

int fill_vertex_with_edges_to_following_vertices(graph_t graph, unsigned int vertex_index, unsigned int neighbor_min,
                                                 unsigned int neighbor_max);

graph_t generate(unsigned int vertex_amount, unsigned int neighbor_min, unsigned int neighbor_max) {
    if (args_not_valid(vertex_amount, neighbor_min, neighbor_max))
        return NULL;

    graph_t graph = graph_create(vertex_amount);

    for (unsigned int i = 0; i < vertex_amount; i++) {

        if (!fill_vertex_with_edges_to_following_vertices(graph, i, neighbor_min, neighbor_max)) {
            graph_free(graph);
            return NULL;
        }

        unsigned int current_adj_list_length = graph_get_adj_list_length(graph, i);
        int current_vertex_is_lacking_neighbors = current_adj_list_length < neighbor_min;
        if (current_vertex_is_lacking_neighbors) {
            fill_vertex_lacking_neighbors(graph, i, neighbor_min, neighbor_max);
        }
    }
    return graph;
}

int fill_vertex_with_edges_to_following_vertices(graph_t graph, unsigned int vertex_index, unsigned int neighbor_min,
                                                 unsigned int neighbor_max) {
    unsigned int current_adj_list_length = graph_get_adj_list_length(graph, vertex_index);
    unsigned int smallest_possible_min = max(neighbor_min, current_adj_list_length);
    unsigned int random_neighbor_count = random_number_between(smallest_possible_min, neighbor_max);
    unsigned int vertex_amount = graph_get_vertex_count(graph);
    unsigned int left_count = vertex_amount - vertex_index - 1;
    unsigned int neighbors_to_add_count = min(left_count, random_neighbor_count - current_adj_list_length);

    if (random_neighbor_count < neighbor_min) {
        graph_free(graph);
        return 0;
    }

    for (unsigned int j = 1; j <= neighbors_to_add_count; j++) {
        graph_add_edge(graph, vertex_index, vertex_index + j);
    }

    return 1;
}


void
fill_vertex_lacking_neighbors(graph_t graph, unsigned int lacking, unsigned int neighbor_min,
                              unsigned int neighbor_max) {

    for (unsigned int j = lacking - 1; j != 0; j--) {
        unsigned int lacking_adj_list_length = graph_get_adj_list_length(graph, lacking);
        if (lacking_adj_list_length >= neighbor_min) {
            break;
        }

        unsigned int j_adj_list_length = graph_get_adj_list_length(graph, j);
        int space_left_for_neighbors = j_adj_list_length + 1 <= neighbor_max;
        if (space_left_for_neighbors && graph_edge_not_exists(graph, lacking, j)) {
            graph_add_edge(graph, lacking, j);
        }
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
    return n * (n - 1) / 2;
}


unsigned int random_uint(unsigned int limit) {
    unsigned int random_number;
    FILE *f = fopen("/dev/random", "r");
    fread(&random_number, sizeof random_number, 1, f);
    fclose(f);
    return random_number % (limit + 1);
}

unsigned int random_number_between(unsigned int from, unsigned int to) {
    if (from > to) {
        unsigned int temp = to;
        to = from;
        from = temp;
    }

    unsigned int length = to - from;

    return from + (random_uint(length));
}

unsigned int min(unsigned int first, unsigned int second) {
    return first > second ? second : first;
}

unsigned int max(unsigned int first, unsigned int second) {
    return first > second ? first : second;
}



