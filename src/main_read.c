#include <stdlib.h>
#include <time.h>
#include "graph_read.h"
#include "graph_dfs.h"
#include "alternative/alt_graph_dfs.h"

#define DECIMAL_BASE 10
#define EXPECTED_ARG_COUNT 3
static clock_t GLOBAL_CLOCK;

struct args {
    char *result_file;
    unsigned int start_vertex;
};

inline void print_usage();

inline struct args construct_args(int argc, char **argv);

inline void start_clock();

inline void stop_clock(char *format);

int main(int argc, char **argv) {
    struct args args = construct_args(argc, argv);

    start_clock();
    graph_t graph = graph_read(args.result_file);
    if (graph == NULL) {
        printf("Graph cannot be generated from file!\n");
        return 1;
    }
    stop_clock("Graph generation took %f seconds \n");

    graph_print(graph);

    start_clock();
    dfs_state_t result = graph_dfs(graph, args.start_vertex);
    stop_clock("DFS took %f seconds \n");

    start_clock();
    alt_dfs_state_t alt_result = alt_graph_dfs(graph, args.start_vertex);
    stop_clock("Simpler DFS took %f seconds \n");

    alt_dfs_state_print(alt_result);

    dfs_state_free(result);
    alt_dfs_state_free(alt_result);
    graph_free(graph);

    return 0;
}

void print_usage() {
    printf("Usage: lab_1_read "
           "<file_path> "
           "<start_vertex> "
    );
}

struct args construct_args(int argc, char **argv) {
    if (argc != EXPECTED_ARG_COUNT) {
        print_usage();
        exit(1);
    }

    char *file_path = argv[1];
    char *start_vertex_str = argv[2];

    unsigned int start_vertex = strtoul(start_vertex_str, NULL, DECIMAL_BASE);

    struct args args = {
            file_path,
            start_vertex
    };

    return args;
}

void start_clock() {
    GLOBAL_CLOCK = clock();
}

void stop_clock(char *format) {
    GLOBAL_CLOCK = clock() - GLOBAL_CLOCK;
    double time_taken = ((double) GLOBAL_CLOCK) / CLOCKS_PER_SEC; // in seconds
    printf(format, time_taken);
}
