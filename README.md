<h1 align="center">Simple graph DFS demonstration</h1>

<p align="center">A C program which generates a graph, applies DFS algorithm, writes the graph and resulting DFS subgraph to file</p>

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
