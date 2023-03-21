//
// Created by edvin on 23.2.28.
//

#include "graph.h"

#ifndef LAB_1_ALT_GRAPH_DFS_H
#define LAB_1_ALT_GRAPH_DFS_H

typedef struct alt_dfs_state_instance_t *alt_dfs_state_t;

alt_dfs_state_t alt_graph_dfs(graph_t graph, unsigned int start);

void alt_dfs_state_print(alt_dfs_state_t state);

linked_list_t alt_dfs_state_path(alt_dfs_state_t state);

void alt_dfs_state_free(alt_dfs_state_t state);


#endif //LAB_1_ALT_GRAPH_DFS_H
