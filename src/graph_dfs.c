//
// Created by edvin on 23.2.28.
//

#include <malloc.h>
#include "stack.h"
#include "graph_dfs.h"

#define VISITED 1;
#define NOT_VISITED 0;

void graph_dfs(graph_t graph, unsigned int start) {
    stack_t stack = stack_create();
    unsigned int vertex_count = graph_get_vertex_count(graph);
    if (start >= vertex_count)
        return;

    unsigned int *visited = calloc(vertex_count, sizeof *visited);

    visited[start] = VISITED;
}