//
// Created by edvin on 23.2.28.
//

#include <malloc.h>
#include "stack.h"
#include "alt_graph_dfs.h"

#define VISITED 1;
#define NOT_VISITED 0;

struct alt_dfs_state_instance_t {
    unsigned int *visited;
    unsigned int vertex_count;
    graph_t graph;
    linked_list_t path;
    stack_t stack;
};


inline void alt_add_non_visited_neighbors_to_stack(alt_dfs_state_t state, unsigned int vertex);

inline unsigned int alt_vertex_not_visited(alt_dfs_state_t state, unsigned int vertex);

inline alt_dfs_state_t alt_init_state(graph_t graph);

inline void alt_mark_as_visited(alt_dfs_state_t state, unsigned int vertex);

inline void alt_push_to_stack(alt_dfs_state_t state, unsigned int to);

inline unsigned int alt_pop_next_vertex(alt_dfs_state_t state, unsigned int *popped_to);

inline unsigned int alt_state_stack_is_not_empty(alt_dfs_state_t state);

inline void alt_add_to_path(alt_dfs_state_t state, unsigned int vertex);

alt_dfs_state_t alt_graph_dfs(graph_t graph, unsigned int start) {
    if (start >= graph_get_vertex_count(graph))
        return NULL;

    alt_dfs_state_t state = alt_init_state(graph);

    unsigned int current = start;

    alt_add_to_path(state, current);
    alt_mark_as_visited(state, current);
    alt_add_non_visited_neighbors_to_stack(state, current);

    while (alt_state_stack_is_not_empty(state)) {
        alt_pop_next_vertex(state, &current);
        alt_add_to_path(state, current);
        alt_mark_as_visited(state, current);
        alt_add_non_visited_neighbors_to_stack(state, current);
    }


    return state;
}

void alt_add_non_visited_neighbors_to_stack(alt_dfs_state_t state, unsigned int vertex) {
    linked_list_t list = graph_get_adj_list(state->graph, vertex);
    while (linked_list_is_not_empty(list)) {
        unsigned int head = linked_list_head(list);
        if (alt_vertex_not_visited(state, head)) {
            alt_push_to_stack(state, head);
        }
        list = linked_list_tail(list);
    }
}

unsigned int alt_vertex_not_visited(alt_dfs_state_t state, unsigned int vertex) {
    return state->visited[vertex] == NOT_VISITED;
}

alt_dfs_state_t alt_init_state(graph_t graph) {
    alt_dfs_state_t state = malloc(sizeof(*state));

    state->vertex_count = graph_get_vertex_count(graph);
    state->visited = calloc(state->vertex_count, sizeof *(state->visited));
    state->graph = graph;
    state->stack = stack_create();
    state->path = linked_list_create();

    return state;
}

void alt_mark_as_visited(alt_dfs_state_t state, unsigned int vertex) {
    state->visited[vertex] = VISITED;
}

void alt_push_to_stack(alt_dfs_state_t state, unsigned int to) {
    stack_push(state->stack, to);
}

unsigned int alt_state_stack_is_not_empty(alt_dfs_state_t state) {
    return stack_is_not_empty(state->stack);
}

unsigned int alt_pop_next_vertex(alt_dfs_state_t state, unsigned int *popped_to) {
    return
            stack_pop(state->stack, popped_to);
}

void alt_dfs_state_free(alt_dfs_state_t state) {
    free(state->visited);
    stack_free(state->stack);
    linked_list_free(state->path);
    free(state);
}

void alt_dfs_state_print(alt_dfs_state_t state) {
    printf("\nVisited vertices: \n");

    linked_list_t reversed_path = linked_list_reverse(state->path);
    linked_list_print(reversed_path, "%d -> ");
    linked_list_free(reversed_path);

    printf("\n");
}

void alt_add_to_path(alt_dfs_state_t state, unsigned int vertex) {
    linked_list_append(state->path, vertex);
}

linked_list_t alt_dfs_state_path(alt_dfs_state_t state) {
    return state->path;
}
