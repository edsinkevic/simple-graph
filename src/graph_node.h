//
// Created by edvin on 23.2.26.
//

#ifndef LAB_1_GRAPH_NODE_H
#define LAB_1_GRAPH_NODE_H

typedef struct graph_node_instance_t *graph_node_t;

graph_node_t graph_node_create(unsigned int vertex_id);

void graph_node_set_next(graph_node_t, graph_node_t);

graph_node_t graph_node_get_next(graph_node_t);

int graph_node_get_vertex(graph_node_t);

void graph_node_print(graph_node_t);

void graph_node_free(graph_node_t);

unsigned int graph_node_length(graph_node_t);

int graph_node_vertex_exists(graph_node_t node, unsigned int vertex);

int graph_node_is_empty(graph_node_t node);

int graph_node_is_not_empty(graph_node_t node);

#endif //LAB_1_GRAPH_NODE_H
