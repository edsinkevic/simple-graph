#include "graph_read.h"
#include "tests/test_graph.h"
#include "tests/test_graph_node.h"
#include "tests/test_graph_generate.h"
#include "tests/test_graph_read.h"
#include "tests/test_stack.h"

int main() {
    int REPEAT_COUNT = 1000;
    test_graph_node();
    test_graph();
    for (int i = 0; i < REPEAT_COUNT; i++) {
        test_generate(20, 2, 10);
    }

    //test_generate(3000, 40, 500);
    test_graph_read();

    test_stack();

    return 0;
}
