//
// Created by edvin on 23.3.10.
//

#include <assert.h>
#include <stddef.h>
#include "test_graph_dfs.h"
#include "graph_dfs.h"
#include "graph_read.h"

void test_graph_dfs() {
    unsigned int test_vertex_count = 7;
    graph_t graph = graph_read("../data/test");
    assert(graph != NULL);
    assert(graph_get_vertex_count(graph) == test_vertex_count);

    dfs_state_t state = graph_dfs(graph, 0);
    dfs_state_print(state);

    graph_t sub_graph = dfs_state_sub_graph(state);

    assert(graph_edge_exists(sub_graph, 0, 1));
    assert(graph_edge_exists(sub_graph, 0, 2));
    assert(graph_edge_exists(sub_graph, 2, 4));
    assert(graph_edge_exists(sub_graph, 3, 6));
    assert(graph_edge_exists(sub_graph, 3, 5));
    assert(graph_edge_exists(sub_graph, 4, 3));

    dfs_state_free(state);
}
