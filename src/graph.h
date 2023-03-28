//
// Created by edvin on 23.2.26.
//

#ifndef LAB_1_GRAPH_H
#define LAB_1_GRAPH_H

#include "linked_list.h"

#include <stdio.h>

typedef struct graph_instance_t *graph_t;

graph_t graph_create(unsigned int size);

void graph_free(graph_t);

void graph_add_edge(graph_t graph, unsigned int from, unsigned int to);

void graph_print(graph_t);

void graph_print_to_stream(graph_t, FILE *stream);

void graph_adj_list_print_to_stream(graph_t graph, FILE *stream, int skip_empty);

unsigned int graph_get_vertex_count(graph_t);

linked_list_t graph_get_adj_list(graph_t, unsigned int index);

unsigned int graph_get_adj_list_length(graph_t, unsigned int index);

int graph_edge_exists(graph_t graph, unsigned int in, unsigned int vertex);

int graph_edge_not_exists(graph_t graph, unsigned int in, unsigned int vertex);

void graph_increase_size(graph_t graph, unsigned int required_size);

int graph_is_empty(graph_t graph);

int graph_is_not_empty(graph_t graph);

#endif //LAB_1_GRAPH_H
