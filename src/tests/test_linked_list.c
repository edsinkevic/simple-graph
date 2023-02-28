//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_linked_list.h"
#include "linked_list.h"

void test_linked_list() {
    linked_list_t first_list = linked_list_create();
    linked_list_append(first_list, 0);
    linked_list_append(first_list, 1);
    linked_list_t second_list = linked_list_tail(first_list);
    linked_list_t second_list_tail = linked_list_tail(second_list);
    assert(linked_list_is_empty(second_list_tail));
    assert(linked_list_length(first_list) == 2);
    assert(linked_list_length(second_list) == 1);
    assert(linked_list_length(NULL) == 0);

    linked_list_free(first_list);
}