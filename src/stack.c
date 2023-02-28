//
// Created by edvin on 23.2.28.
//

#include <malloc.h>
#include "stack.h"

struct stack_node_instance_t {
    unsigned int value;
    struct stack_node_instance_t *next;
};

struct stack_instance_t {
    struct stack_node_instance_t *head;
};


stack_t stack_create() {
    stack_t stack = malloc(sizeof *stack);
    stack->head = NULL;

    return stack;
}

int stack_pop(stack_t stack, unsigned int *popped_ptr) {
    if (stack_is_empty(stack))
        return 0;

    *popped_ptr = stack->head->value;
    struct stack_node_instance_t *temp = stack->head;
    stack->head = stack->head->next;

    free(temp);

    return 1;
}

int stack_push(stack_t stack, unsigned int to_push) {
    if (stack == NULL)
        return 0;

    struct stack_node_instance_t *node = malloc(sizeof *node);

    node->value = to_push;
    node->next = stack->head;

    stack->head = node;

    return 1;
}

int stack_is_empty(stack_t stack) {
    return stack == NULL || stack->head == NULL ? 1 : 0;
}

int stack_is_not_empty(stack_t stack) {
    return !stack_is_empty(stack);
}

void stack_free(stack_t stack) {
    if (stack == NULL)
        return;

    struct stack_node_instance_t *head = stack->head;

    while (head != NULL) {
        struct stack_node_instance_t *temp = head;
        head = head->next;
        free(temp);
    }

    free(stack);
}
