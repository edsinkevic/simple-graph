//
// Created by edvin on 23.2.28.
//

#include <assert.h>
#include <stddef.h>
#include "test_stack.h"
#include "stack.h"

void test_stack() {
    unsigned int popped = 0;

    stack_t stack = NULL;
    assert(stack_is_empty(stack));
    assert(!stack_push(stack, 1));
    assert(!stack_pop(stack, &popped));
    stack = stack_create();

    assert(stack_push(stack, 1));
    assert(stack_is_not_empty(stack));
    assert(stack_push(stack, 2));
    assert(stack_pop(stack, &popped));
    assert(popped == 2);
    assert(stack_pop(stack, &popped));
    assert(popped == 1);
    assert(stack_is_empty(stack));
    assert(!stack_pop(stack, &popped));
    assert(popped == 1);


    stack_free(stack);
}
