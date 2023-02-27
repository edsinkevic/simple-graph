#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "generate.h"
#include "graph_node.h"
#include "graph_read.h"

void test_graph_node();

void test_graph();

void test_generate();

void test_graph_read();

int main() {
    int REPEAT_COUNT = 1000;
    test_graph_node();
    test_graph();
    for (int i = 0; i < REPEAT_COUNT; i++) {
        test_generate();
    }
    test_graph_read();

    return 0;
}

void test_graph_node() {
    graph_node_t first_node = graph_node_create(0);
    graph_node_t second_node = graph_node_create(1);
    graph_node_set_next(first_node, second_node);
    assert(graph_node_get_next(first_node) == second_node);
    assert(graph_node_get_next(second_node) == NULL);
    assert(graph_node_length(first_node) == 2);
    assert(graph_node_length(second_node) == 1);
    assert(graph_node_length(NULL) == 0);
    graph_node_free(first_node);
}


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

void test_generate() {
    unsigned int intended_vertex_count = 20;
    unsigned int neighbor_min = 2;
    unsigned int neighbor_max = 12;
    graph_t graph = generate(intended_vertex_count, neighbor_min, neighbor_max);
    assert(graph != NULL);
    unsigned int vertex_count = graph_get_vertex_count(graph);
    assert(vertex_count == intended_vertex_count);

    for (unsigned int i = 0; i < vertex_count; i++) {
        unsigned int length = graph_get_adj_list_length(graph, i);
//        printf("Checking constraints for vertex number %d\n", i);
//        graph_node_print(graph_get_adj_list(graph, i));
//        printf("\n");
//        printf("Length: %d\n", length);
        assert(length >= neighbor_min && length <= neighbor_max);
    }

    graph_print(graph);

    graph_free(graph);
}


void test_graph_read() {
    unsigned int test_vertex_count = 7;
    graph_t graph = graph_read("../data/test");
    assert(graph != NULL);
    assert(graph_get_vertex_count(graph) == test_vertex_count);
    assert(graph_get_adj_list_length(graph, 0) == 2);
    assert(graph_get_adj_list_length(graph, 1) == 1);
    assert(graph_get_adj_list_length(graph, 2) == 2);
    assert(graph_get_adj_list_length(graph, 3) == 3);
    assert(graph_get_adj_list_length(graph, 4) == 2);
    assert(graph_get_adj_list_length(graph, 5) == 1);
    assert(graph_get_adj_list_length(graph, 6) == 1);

    assert(graph_edge_exists(graph, 0, 2));
    assert(graph_edge_exists(graph, 0, 1));

    assert(graph_edge_exists(graph, 1, 0));

    assert(graph_edge_exists(graph, 2, 4));
    assert(graph_edge_exists(graph, 2, 0));

    assert(graph_edge_exists(graph, 3, 6));
    assert(graph_edge_exists(graph, 3, 5));
    assert(graph_edge_exists(graph, 3, 4));


    assert(graph_edge_exists(graph, 4, 3));
    assert(graph_edge_exists(graph, 4, 2));

    assert(graph_edge_exists(graph, 5, 3));

    assert(graph_edge_exists(graph, 6, 3));
}