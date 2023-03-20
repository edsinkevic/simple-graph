# Simple graph depth-first search demonstration
A C program which generates a graph, applies DFS algorithm, writes the graph and resulting DFS subgraph to respective files.

It takes the file paths as parameters, the required amount of vertices in the graph, the minimum and maximum amounts 
of neighbors for each vertex, and, finally, a vertex index to start DFS from.

Won't work on Windows, because the current implementation uses '/dev/random' file to generate random numbers.

# How to run
## Build the executables lab_1 and lab_1_tests
```
  cmake -B target &&\
  cd target &&\
  make
```

## Run lab_1
```
  target/lab_1 <result_file_path> <sub_graph_result_file_path> <vertex_count> <neighbor_min> <neighbor_max> <start_vertex>
```

## Run lab_1_tests (TODO: right now the tests only work if you are in 'target' directory)
```
  cd target && \
  ./lab_1_tests
```
