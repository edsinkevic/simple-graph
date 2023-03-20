//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include "test_graph_generate.h"
#include "graph.h"
#include "graph_generate.h"

void test_graph_generate(unsigned int intended_vertex_count, unsigned int neighbor_min, unsigned int neighbor_max) {
    clock_t t;
    t = clock();
    graph_t graph = graph_generate(intended_vertex_count, neighbor_min, neighbor_max);
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
    printf("%f seconds \n", time_taken);

    graph_print(graph);

    assert(graph != NULL);
    unsigned int vertex_count = graph_get_vertex_count(graph);
    assert(vertex_count == intended_vertex_count);

    for (unsigned int i = 0; i < vertex_count; i++) {
        unsigned int length = graph_get_adj_list_length(graph, i);
        assert(graph_edge_not_exists(graph, i, i));
        assert(length <= neighbor_max);
        assert(length >= neighbor_min);
    }

    FILE *file = fopen("../data/test_write", "w+");
    graph_print_to_stream(graph, file);

    graph_free(graph);
}
