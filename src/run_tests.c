//
// Created by edvin on 23.3.19.
//

#include "tests/include.h"

int main() {
    test_linked_list();
    test_graph();

    int REPEAT_COUNT = 1000;
#if 0
    for (int i = 0; i < REPEAT_COUNT; i++) {
        test_graph_generate(100, 2, 50);
    }
#endif

    test_graph_generate(15, 2, 2);
    test_graph_read();

    test_stack();
    test_graph_dfs();

    return 0;
}
