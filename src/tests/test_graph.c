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
        linked_list_t list = graph_get_adj_list(graph, i);
        assert(linked_list_is_empty(list));
    }

    int from = 0;
    int to = 1;

    graph_add_edge(graph, from, to);
    linked_list_t from_node = graph_get_adj_list(graph, from);
    linked_list_t to_node_empty = graph_get_adj_list(graph, to);
    assert(linked_list_is_empty(to_node_empty));
    assert(linked_list_head(from_node) == to);
    assert(graph_get_adj_list_length(graph, 0) == 1);
    assert(graph_get_adj_list_length(graph, 1) == 0);
    assert(linked_list_is_empty(to_node_empty));

    graph_add_edge(graph, to, from);
    linked_list_t to_node = graph_get_adj_list(graph, to);
    assert(linked_list_head(to_node) == from);
    assert(graph_get_adj_list_length(graph, 1) == 1);
    assert(graph_edge_exists(graph, from, to));
    assert(graph_edge_exists(graph, to, from));

    graph_free(graph);
}
