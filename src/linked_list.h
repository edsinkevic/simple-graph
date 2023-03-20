//
// Created by edvin on 23.2.26.
//

#ifndef LAB_1_LINKED_LIST_H
#define LAB_1_LINKED_LIST_H

#include <stdio.h>

typedef struct linked_list_instance_t *linked_list_t;

linked_list_t linked_list_create();

void linked_list_append(linked_list_t list, unsigned int value);

linked_list_t linked_list_tail(linked_list_t list);

int linked_list_head(linked_list_t list);

int linked_list_pop_head(linked_list_t list, unsigned int *popped);

void linked_list_print(linked_list_t list, char *format);

void linked_list_print_to_stream(linked_list_t list, char *format, FILE *stream);

void linked_list_free(linked_list_t list);

unsigned int linked_list_length(linked_list_t list);

int linked_list_value_exists(linked_list_t list, unsigned int value);

int linked_list_is_empty(linked_list_t list);

int linked_list_is_not_empty(linked_list_t linked_list);

linked_list_t linked_list_reverse(linked_list_t linked_list);

#endif //LAB_1_LINKED_LIST_H
