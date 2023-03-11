//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_graph_read.h"
#include "graph.h"
#include "graph_read.h"

void test_graph_read() {
    unsigned int test_vertex_count = 7;
    graph_t graph = graph_read("../data/test");
    assert(graph != NULL);
    assert(graph_get_vertex_count(graph) == test_vertex_count);

    graph_print(graph);
    assert(graph_get_adj_list_length(graph, 0) == 2);
    assert(graph_get_adj_list_length(graph, 1) == 0);
    assert(graph_get_adj_list_length(graph, 2) == 2);
    assert(graph_get_adj_list_length(graph, 3) == 3);
    assert(graph_get_adj_list_length(graph, 4) == 2);
    assert(graph_get_adj_list_length(graph, 5) == 1);
    assert(graph_get_adj_list_length(graph, 6) == 1);

    assert(graph_edge_exists(graph, 0, 2));
    assert(graph_edge_exists(graph, 0, 1));

    assert(graph_edge_exists(graph, 2, 4));
    assert(graph_edge_exists(graph, 2, 0));

    assert(graph_edge_exists(graph, 3, 6));
    assert(graph_edge_exists(graph, 3, 5));
    assert(graph_edge_exists(graph, 3, 4));


    assert(graph_edge_exists(graph, 4, 3));
    assert(graph_edge_exists(graph, 4, 2));

    assert(graph_edge_exists(graph, 5, 3));

    assert(graph_edge_exists(graph, 6, 3));

    graph_free(graph);
}
