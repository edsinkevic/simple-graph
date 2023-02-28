//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_graph.h"
#include "graph.h"

void test_graph() {
    int size = 10;
    graph_t graph = graph_create(size);
    unsigned int count = graph_get_vertex_count(graph);
    assert(count == size);
    for (int i = 0; i < count; i++) {
        graph_node_t node = graph_get_adj_list(graph, i);
        assert(graph_node_get_next(node) == NULL);
    }

    int from = 0;
    int to = 1;

    graph_add_edge(graph, from, to);
    graph_node_t from_node = graph_get_adj_list(graph, from);
    graph_node_t to_node_empty = graph_get_adj_list(graph, to);
    assert(graph_node_get_vertex(from_node) == to);
    assert(graph_get_adj_list_length(graph, 0) == 1);
    assert(graph_get_adj_list_length(graph, 1) == 0);
    assert(graph_node_is_empty(to_node_empty));

    graph_add_edge(graph, to, from);
    graph_node_t to_node = graph_get_adj_list(graph, to);
    assert(graph_node_get_vertex(to_node) == from);
    assert(graph_get_adj_list_length(graph, 1) == 1);
    assert(graph_edge_exists(graph, from, to));
    assert(graph_edge_exists(graph, to, from));

    graph_free(graph);
}
