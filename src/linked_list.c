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
    unsigned int tail_ptr_count;
    linked_list_t *tails;
};

linked_list_t linked_list_create() {
    linked_list_t list = malloc(sizeof *list);
    list->tail_ptr_count = 0;
    list->tails = NULL;
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

    linked_list_t tail_list = malloc(sizeof *tail_list);
    tail_list->tail_ptr_count = 0;
    tail_list->head = list->head->next;
    tail_list->tails = NULL;

    list->tail_ptr_count += 1;
    if (list->tails == NULL) {
        list->tails = malloc(sizeof(list->tails) * list->tail_ptr_count);
    } else {
        list->tails = realloc(list->tails, sizeof(list->tails) * list->tail_ptr_count);
    }
    list->tails[list->tail_ptr_count - 1] = tail_list;

    return tail_list;
}

int linked_list_head(linked_list_t list) {
    return linked_list_is_empty(list) ? -1 : list->head->value;
}

void linked_list_free(linked_list_t list) {
    struct linked_list_node_instance_t *temp;
    struct linked_list_node_instance_t *head = list->head;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    for (int i = 0; i < list->tail_ptr_count; i++) {
        free(list->tails[i]);
    }

    free(list);
}

unsigned int linked_list_length(linked_list_t list) {
    if (linked_list_is_empty(list))
        return 0;

    unsigned int length = 0;
    struct linked_list_node_instance_t *head = list->head;
    while (head != NULL) {
        length += 1;
        head = head->next;
    }

    return length;
}

int linked_list_value_exists(linked_list_t list, unsigned int value) {
    struct linked_list_node_instance_t *head = list->head;
    while (head != NULL) {
        if (head->value == value)
            return 1;
        head = head->next;
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

linked_list_t linked_list_reverse(linked_list_t linked_list) {
    if (linked_list == NULL) {
        return NULL;
    }

    linked_list_t list = linked_list_create();
    struct linked_list_node_instance_t *head = linked_list->head;
    while (head != NULL) {
        linked_list_append(list, head->value);
        head = head->next;
    }
    return list;
}
