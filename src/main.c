#include "graph_read.h"
#include "tests/test_graph.h"
#include "tests/test_linked_list.h"
#include "tests/test_graph_generate.h"
#include "tests/test_graph_read.h"
#include "tests/test_stack.h"
#include "tests/test_graph_dfs.h"

int main() {
    test_linked_list();
    test_graph();

    int REPEAT_COUNT = 1000;
    for (int i = 0; i < REPEAT_COUNT; i++) {
        test_graph_generate(100, 2, 50);
    }

    //test_graph_generate(10000, 40, 500);
    test_graph_read();

    test_stack();
    test_graph_dfs();

    return 0;
}
