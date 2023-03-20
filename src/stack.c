//
// Created by edvin on 23.2.28.
//

#include <malloc.h>
#include "stack.h"
#include "linked_list.h"

struct stack_instance_t {
    linked_list_t head;
};

stack_t stack_create() {
    stack_t stack = malloc(sizeof *stack);
    stack->head = linked_list_create();

    return stack;
}

int stack_pop(stack_t stack, unsigned int *popped_ptr) {
    if (stack_is_empty(stack))
        return 0;

    if (linked_list_pop_head(stack->head, popped_ptr))
        return 1;

    return 0;
}

int stack_push(stack_t stack, unsigned int to_push) {
    if (stack == NULL)
        return 0;

    linked_list_append(stack->head, to_push);

    return 1;
}

int stack_is_empty(stack_t stack) {
    return stack == NULL || stack->head == NULL || linked_list_is_empty(stack->head) ? 1 : 0;
}

int stack_is_not_empty(stack_t stack) {
    return !stack_is_empty(stack);
}

void stack_free(stack_t stack) {
    if (stack == NULL)
        return;

    linked_list_free(stack->head);
    free(stack);
}

void stack_print(stack_t stack) {
    linked_list_print(stack->head, "%d ->");
}
