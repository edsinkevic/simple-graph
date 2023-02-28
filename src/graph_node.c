//
// Created by edvin on 23.2.26.
//

#include <malloc.h>
#include "graph_node.h"

struct graph_node_instance_t {
    int vertex;
    struct graph_node_instance_t *next;
};

graph_node_t graph_node_create(unsigned int vertex_id) {
    struct graph_node_instance_t *node = malloc(sizeof *node);
    node->vertex = vertex_id;
    node->next = NULL;
    return node;
}

void graph_node_set_next(graph_node_t from, graph_node_t to) {
    from->next = to;
}

void graph_node_print(graph_node_t graph_node) {
    while (graph_node_is_not_empty(graph_node)) {
        char *format = graph_node->next != NULL ? "%d -> " : "%d";
        printf(format, graph_node->vertex);
        graph_node = graph_node->next;
    }
}

graph_node_t graph_node_get_next(graph_node_t node) {
    return graph_node_is_empty(node) ? NULL : node->next;
}

int graph_node_get_vertex(graph_node_t node) {
    return graph_node_is_empty(node) ? -1 : node->vertex;
}

void graph_node_free(graph_node_t node) {
    graph_node_t temp;
    while (graph_node_is_not_empty(node)) {
        temp = node;
        node = graph_node_get_next(node);
        free(temp);
    }
}

unsigned int graph_node_length(graph_node_t node) {
    unsigned int length = 0;
    while (graph_node_is_not_empty(node)) {
        length += 1;
        node = graph_node_get_next(node);
    }

    return length;
}

int graph_node_vertex_exists(graph_node_t node, unsigned int vertex) {
    while (graph_node_is_not_empty(node)) {
        if (graph_node_get_vertex(node) == vertex)
            return 1;
        node = graph_node_get_next(node);
    }

    return 0;
}

int graph_node_is_empty(graph_node_t node) {
    return node == NULL;
}

int graph_node_is_not_empty(graph_node_t node) {
    return !graph_node_is_empty(node);
}