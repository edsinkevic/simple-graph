//
// Created by edvin on 23.2.26.
//

#include <malloc.h>
#include "linked_list.h"

struct linked_list_node_instance_t {
    unsigned int value;
    struct linked_list_node_instance_t *next;
};

struct linked_list_instance_t {
    struct linked_list_node_instance_t *head;
};

linked_list_t linked_list_create() {
    linked_list_t list = malloc(sizeof *list);
    list->head = NULL;
    return list;
}

void linked_list_append(linked_list_t list, unsigned int value) {
    struct linked_list_node_instance_t *node = malloc(sizeof *node);
    node->value = value;
    node->next = list->head;
    list->head = node;
}

void linked_list_print(linked_list_t list) {
    struct linked_list_node_instance_t *head = list->head;
    while (head != NULL) {
        char *format = head->next != NULL ? "%d -> " : "%d";
        printf(format, head->value);
        head = head->next;
    }
}

linked_list_t linked_list_tail(linked_list_t list) {
    if (linked_list_is_empty(list))
        return NULL;

    struct linked_list_node_instance_t *tail_node = list->head->next;

    linked_list_t tail_list = malloc(sizeof *tail_list);
    tail_list->head = list->head->next;

    return tail_list;
}

int linked_list_head(linked_list_t list) {
    return linked_list_is_empty(list) ? -1 : list->head->value;
}

void linked_list_free(linked_list_t list) {
    linked_list_t temp;
    while (linked_list_is_not_empty(list)) {
        temp = list;
        list = linked_list_tail(list);
        free(temp);
    }
}

unsigned int linked_list_length(linked_list_t list) {
    unsigned int length = 0;
    while (linked_list_is_not_empty(list)) {
        length += 1;
        list = linked_list_tail(list);
    }

    return length;
}

int linked_list_value_exists(linked_list_t node, unsigned int value) {
    while (linked_list_is_not_empty(node)) {
        if (linked_list_head(node) == value)
            return 1;
        node = linked_list_tail(node);
    }

    return 0;
}

int linked_list_is_empty(linked_list_t list) {
    return list == NULL || list->head == NULL;
}

int linked_list_is_not_empty(linked_list_t linked_list) {
    return !linked_list_is_empty(linked_list);
}

int linked_list_pop_head(linked_list_t list, unsigned int *popped) {
    if (linked_list_is_empty(list))
        return 0;

    struct linked_list_node_instance_t *head = list->head;

    *popped = head->value;
    list->head = head->next;
    free(head);

    return 1;
}
