//
// Created by edvin on 23.2.26.
//

#include <stddef.h>
#include <malloc.h>
#include "graph.h"
#include "linked_list.h"


struct graph_instance_t {
    unsigned int vertices_count;
    linked_list_t *adj_lists;
};

graph_t graph_create(unsigned int size) {
    struct graph_instance_t *graph = malloc(sizeof *graph);
    graph->vertices_count = size;
    graph->adj_lists = malloc(size * sizeof(graph->adj_lists));

    for (int i = 0; i < size; i++) {
        graph->adj_lists[i] = linked_list_create();
    }
    return graph;
}


void graph_free(graph_t graph) {
    if (graph_is_empty(graph))
        return;

    for (int i = 0; i < graph->vertices_count; i++)
        linked_list_free(graph->adj_lists[i]);

    free(graph->adj_lists);
    free(graph);
}

void graph_add_edge(graph_t graph, unsigned int from, unsigned int to) {
    if (graph_edge_exists(graph, from, to))
        return;

    linked_list_append(graph->adj_lists[from], to);
}

void graph_print(graph_t graph) {
    graph_print_to_stream(graph, stdout);
}

unsigned int graph_get_vertex_count(graph_t graph) {
    return graph->vertices_count;
}

linked_list_t graph_get_adj_list(graph_t graph, unsigned int index) {
    if (graph_is_empty(graph))
        return NULL;

    if (graph->vertices_count <= index)
        return NULL;

    return graph->adj_lists[index];
}

unsigned int graph_get_adj_list_length(graph_t graph, unsigned int index) {
    if (graph_is_empty(graph))
        return 0;

    return linked_list_length(graph_get_adj_list(graph, index));
}

int graph_edge_exists(graph_t graph, unsigned int in, unsigned int vertex) {
    if (graph_is_empty(graph))
        return -1;


    linked_list_t adj_list = graph_get_adj_list(graph, in);

    if (linked_list_is_empty(adj_list))
        return 0;

    return linked_list_value_exists(adj_list, vertex);
}

int graph_edge_not_exists(graph_t graph, unsigned int in, unsigned int vertex) {
    return !graph_edge_exists(graph, in, vertex);
}

void graph_increase_size(graph_t graph, unsigned int required_size) {
    if (required_size <= graph_get_vertex_count(graph))
        return;

    graph->adj_lists = realloc(graph->adj_lists, required_size * sizeof(graph->adj_lists));

    for (unsigned int i = graph_get_vertex_count(graph); i < required_size; i++) {
        graph->adj_lists[i] = linked_list_create();
    }

    graph->vertices_count = required_size;
}

int graph_is_empty(graph_t graph) {
    return graph == NULL;
}

int graph_is_not_empty(graph_t graph) {
    return !graph_is_empty(graph);
}

void graph_print_to_stream(graph_t graph, FILE *stream) {
    char *str = malloc(13 * sizeof(*str));

    for (int i = 0; i < graph->vertices_count; i++) {
        sprintf(str, "%d %s {}\n", i, "%d");
        linked_list_print_to_stream(graph->adj_lists[i], str, stream);
    }
    fprintf(stream, "\n");
}
