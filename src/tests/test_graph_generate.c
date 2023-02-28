//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_graph_generate.h"
#include "graph.h"
#include "graph_generate.h"

void test_graph_generate(unsigned int intended_vertex_count, unsigned int neighbor_min, unsigned int neighbor_max) {
    graph_t graph = graph_generate(intended_vertex_count, neighbor_min, neighbor_max);
    assert(graph != NULL);
    unsigned int vertex_count = graph_get_vertex_count(graph);
    assert(vertex_count == intended_vertex_count);

    for (unsigned int i = 0; i < vertex_count; i++) {
        unsigned int length = graph_get_adj_list_length(graph, i);
        assert(graph_edge_not_exists(graph, i, i));
        assert(length <= neighbor_max);
        assert(length >= neighbor_min);
    }

    graph_free(graph);
}
