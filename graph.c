//
// Created by edvin on 23.2.26.
//

#include <stddef.h>
#include <malloc.h>
#include "graph.h"
#include "graph_node.h"


struct graph_instance_t {
    unsigned int vertices_count;
    graph_node_t *adj_lists;
};

graph_t graph_create(unsigned int size) {
    struct graph_instance_t *graph = malloc(sizeof *graph);
    graph->vertices_count = size;
    graph->adj_lists = malloc(size * sizeof(graph->adj_lists));

    for (int i = 0; i < size; i++) {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}


void graph_free(graph_t graph) {
    if (graph_is_empty(graph))
        return;

    for (int i = 0; i < graph->vertices_count; i++)
        graph_node_free(graph->adj_lists[i]);

    free(graph->adj_lists);
    free(graph);
}

void graph_add_edge(graph_t graph, unsigned int from, unsigned int to) {
    if (graph_edge_exists(graph, from, to))
        return;

    graph_node_t node = graph_node_create(to);
    graph_node_set_next(node, graph->adj_lists[from]);
    graph->adj_lists[from] = node;
}

void graph_print(graph_t graph) {
    for (int i = 0; i < graph->vertices_count; i++) {
        printf("Vertex %d: ", i);
        graph_node_print(graph->adj_lists[i]);
        printf("\n");
    }
    printf("\n");
}

unsigned int graph_get_vertex_count(graph_t graph) {
    return graph->vertices_count;
}

graph_node_t graph_get_adj_list(graph_t graph, unsigned int index) {
    if (graph_is_empty(graph))
        return NULL;

    if (graph->vertices_count <= index)
        return NULL;

    return graph->adj_lists[index];
}

unsigned int graph_get_adj_list_length(graph_t graph, unsigned int index) {
    if (graph_is_empty(graph))
        return 0;

    return graph_node_length(graph_get_adj_list(graph, index));
}

int graph_edge_exists(graph_t graph, unsigned int in, unsigned int vertex) {
    if (graph_is_empty(graph))
        return -1;


    graph_node_t adj_list = graph_get_adj_list(graph, in);

    if (graph_node_is_empty(adj_list))
        return 0;

    return graph_node_vertex_exists(adj_list, vertex);
}

int graph_edge_not_exists(graph_t graph, unsigned int in, unsigned int vertex) {
    return !graph_edge_exists(graph, in, vertex);
}

void graph_increase_size(graph_t graph, unsigned int required_size) {
    if (required_size <= graph_get_vertex_count(graph))
        return;

    graph->adj_lists = realloc(graph->adj_lists, required_size * sizeof(graph->adj_lists));

    for (unsigned int i = graph_get_vertex_count(graph); i < required_size; i++) {
        graph->adj_lists[i] = NULL;
    }

    graph->vertices_count = required_size;
}

int graph_is_empty(graph_t graph) {
    return graph == NULL;
}

int graph_is_not_empty(graph_t graph) {
    return !graph_is_empty(graph);
}

