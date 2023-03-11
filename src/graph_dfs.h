//
// Created by edvin on 23.2.28.
//

#include "graph.h"

#ifndef LAB_1_GRAPH_DFS_H
#define LAB_1_GRAPH_DFS_H

typedef struct dfs_state_instance_t *dfs_state_t;

dfs_state_t graph_dfs(graph_t graph, unsigned int start);

graph_t dfs_state_sub_graph(dfs_state_t state);

void dfs_state_print(dfs_state_t state);

void dfs_state_free(dfs_state_t state);


#endif //LAB_1_GRAPH_DFS_H
