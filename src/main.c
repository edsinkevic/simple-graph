#include <stdlib.h>
#include <time.h>
#include "graph_read.h"
#include "graph_generate.h"
#include "graph_dfs.h"
#include "alternative/alt_graph_dfs.h"

#define DECIMAL_BASE 10
#define EXPECTED_ARG_COUNT 8
static clock_t GLOBAL_CLOCK;

struct args {
    FILE *result_file;
    FILE *sub_graph_result_file;
    unsigned int vertex_count;
    unsigned int neighbor_min;
    unsigned int neighbor_max;
    unsigned int start_vertex;
    char print;
};

inline void print_usage();

inline struct args construct_args(int argc, char **argv);

inline void start_clock();

inline void stop_clock(char *format);

int main(int argc, char **argv) {
    struct args args = construct_args(argc, argv);

    start_clock();
    graph_t graph = graph_generate(args.vertex_count, args.neighbor_min, args.neighbor_max);
    if (graph == NULL) {
        printf("Graph cannot be generated from given parameters!\n");
        return 1;
    }

    stop_clock("Graph generation took %f seconds \n");

    start_clock();
    dfs_state_t result = graph_dfs(graph, args.start_vertex);
    stop_clock("DFS took %f seconds \n");

    if (args.print)
        dfs_state_print(result);


    start_clock();
    alt_dfs_state_t alt_result = alt_graph_dfs(graph, args.start_vertex);
    stop_clock("Simpler DFS took %f seconds \n");


    if (args.print)
        alt_dfs_state_print(alt_result);

    graph_print_to_stream(graph, args.result_file);
    graph_print_to_stream(dfs_state_sub_graph(result), args.sub_graph_result_file);

    dfs_state_free(result);
    alt_dfs_state_free(alt_result);
    graph_free(graph);
    fclose(args.result_file);
    fclose(args.sub_graph_result_file);

    return 0;
}

void print_usage() {
    printf("Usage: lab_1 "
           "<result_file_path> "
           "<sub_graph_result_file_path> "
           "<vertex_count> "
           "<neighbor_min> "
           "<neighbor_max> "
           "<start_vertex> "
           "<should_print>"
    );
}

struct args construct_args(int argc, char **argv) {
    if (argc != EXPECTED_ARG_COUNT) {
        print_usage();
        exit(1);
    }

    char *result_file_path = argv[1];
    char *sub_graph_result_file_path = argv[2];
    char *vertex_count_str = argv[3];
    char *neighbor_min_str = argv[4];
    char *neighbor_max_str = argv[5];
    char *start_vertex_str = argv[6];
    char *should_print_str = argv[7];

    unsigned int vertex_count = strtoul(vertex_count_str, NULL, DECIMAL_BASE);
    unsigned int neighbor_min = strtoul(neighbor_min_str, NULL, DECIMAL_BASE);
    unsigned int neighbor_max = strtoul(neighbor_max_str, NULL, DECIMAL_BASE);
    unsigned int start_vertex = strtoul(start_vertex_str, NULL, DECIMAL_BASE);
    unsigned int should_print = strtoul(should_print_str, NULL, DECIMAL_BASE);

    FILE *result_file = fopen(result_file_path, "w+");

    if (result_file == NULL) {
        printf("Could not open graph result result_file!\n");
        exit(1);
    }

    FILE *subgraph_result_file = fopen(sub_graph_result_file_path, "w+");

    if (subgraph_result_file == NULL) {
        printf("Could not open DFS sub graph result result_file!\n");
        exit(1);
    }

    struct args args = {
            result_file,
            subgraph_result_file,
            vertex_count,
            neighbor_min,
            neighbor_max,
            start_vertex,
            should_print
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
