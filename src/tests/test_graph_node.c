//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_graph_node.h"
#include "graph_node.h"

void test_graph_node() {
    graph_node_t first_node = graph_node_create(0);
    graph_node_t second_node = graph_node_create(1);
    graph_node_set_next(first_node, second_node);
    assert(graph_node_get_next(first_node) == second_node);
    assert(graph_node_get_next(second_node) == NULL);
    assert(graph_node_length(first_node) == 2);
    assert(graph_node_length(second_node) == 1);
    assert(graph_node_length(NULL) == 0);

    int count = 0;
    graph_node_free(first_node);
}