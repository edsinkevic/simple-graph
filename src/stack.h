//
// Created by edvin on 23.2.28.
//

#ifndef LAB_1_STACK_H
#define LAB_1_STACK_H

typedef struct stack_instance_t *stack_t;

stack_t stack_create();

int stack_pop(stack_t stack, unsigned int *popped_ptr);

int stack_push(stack_t stack, unsigned int to_push);

void stack_free(stack_t stack);

int stack_is_empty(stack_t stack);

int stack_is_not_empty(stack_t stack);

void stack_print(stack_t stack);

#endif //LAB_1_STACK_H
