//
// Created by edvin on 23.2.28.
//

#include <malloc.h>
#include "stack.h"
#include "graph_dfs.h"

#define VISITED 1;
#define NOT_VISITED 0;

struct dfs_state_instance_t {
    unsigned int *visited;
    unsigned int vertex_count;
    graph_t graph;
    graph_t sub_graph;
    linked_list_t path;
    stack_t stack_from;
    stack_t stack_to;
};


inline void add_non_visited_neighbors_to_stack(dfs_state_t state, unsigned int vertex);

inline unsigned int vertex_not_visited(dfs_state_t state, unsigned int vertex);

inline dfs_state_t init_state(graph_t graph);

inline void mark_as_visited(dfs_state_t state, unsigned int vertex);

inline void push_to_stack(dfs_state_t state, unsigned int from, unsigned int to);

inline unsigned int pop_next_vertex(dfs_state_t state, unsigned int *popped_from, unsigned int *popped_to);

inline unsigned int state_stack_is_not_empty(dfs_state_t state);

inline void add_edge_sub_graph(dfs_state_t state, unsigned int from, unsigned int to);

inline void add_to_path(dfs_state_t state, unsigned int vertex);

dfs_state_t graph_dfs(graph_t graph, unsigned int start) {
    if (start >= graph_get_vertex_count(graph))
        return NULL;

    dfs_state_t state = init_state(graph);

    unsigned int from;
    unsigned int current = start;

    add_to_path(state, current);
    mark_as_visited(state, current);
    add_non_visited_neighbors_to_stack(state, current);

    while (state_stack_is_not_empty(state)) {
        pop_next_vertex(state, &from, &current);
        add_to_path(state, current);
        add_non_visited_neighbors_to_stack(state, current);
        add_edge_sub_graph(state, from, current);
    }

    return state;
}

void add_non_visited_neighbors_to_stack(dfs_state_t state, unsigned int vertex) {
    linked_list_t list = graph_get_adj_list(state->graph, vertex);
    while (linked_list_is_not_empty(list)) {
        unsigned int head = linked_list_head(list);
        if (vertex_not_visited(state, head)) {
            mark_as_visited(state, head);
            push_to_stack(state, vertex, head);
        }
        list = linked_list_tail(list);
    }
}

unsigned int vertex_not_visited(dfs_state_t state, unsigned int vertex) {
    return state->visited[vertex] == NOT_VISITED;
}

dfs_state_t init_state(graph_t graph) {
    dfs_state_t state = malloc(sizeof(*state));

    state->vertex_count = graph_get_vertex_count(graph);
    state->visited = calloc(state->vertex_count, sizeof *(state->visited));
    state->graph = graph;
    state->sub_graph = graph_create(state->vertex_count);
    state->stack_from = stack_create();
    state->stack_to = stack_create();
    state->path = linked_list_create();

    return state;
}

void mark_as_visited(dfs_state_t state, unsigned int vertex) {
    state->visited[vertex] = VISITED;
}

void push_to_stack(dfs_state_t state, unsigned int from, unsigned int to) {
    stack_push(state->stack_from, from);
    stack_push(state->stack_to, to);
}

unsigned int state_stack_is_not_empty(dfs_state_t state) {
    return stack_is_not_empty(state->stack_from);
}

unsigned int pop_next_vertex(dfs_state_t state, unsigned int *popped_from, unsigned int *popped_to) {
    return
            stack_pop(state->stack_from, popped_from) &&
            stack_pop(state->stack_to, popped_to);
}

void dfs_state_free(dfs_state_t state) {
    free(state->visited);
    stack_free(state->stack_from);
    stack_free(state->stack_to);
    graph_free(state->sub_graph);
    linked_list_free(state->path);
    free(state);
}

graph_t dfs_state_sub_graph(dfs_state_t state) {
    return state->sub_graph;
}

void dfs_state_print(dfs_state_t state) {
    printf("\nVisited vertices: \n");

    linked_list_t reversed_path = linked_list_reverse(state->path);
    linked_list_print(reversed_path, "%d -> ");
    linked_list_free(reversed_path);

    printf("\n");
    //graph_print(state->sub_graph);
}

void dfs_state_print_path(dfs_state_t state) {
    linked_list_print(state->path, "%d -> ");
    printf("\n");
}

void add_edge_sub_graph(dfs_state_t state, unsigned int from, unsigned int to) {
    if (graph_edge_exists(state->graph, from, to))
        graph_add_edge(state->sub_graph, from, to);
}

void add_to_path(dfs_state_t state, unsigned int vertex) {
    linked_list_append(state->path, vertex);
}
