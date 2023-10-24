#ifndef _STACK_LIST_H
#define _STACK_LIST_H

#include <assert.h>
#include <stdlib.h>

#include "linked_list.h"

#define STARTING_SIZE 256
#define STACK_EXIT_CODE INT_MAX

typedef struct {
  Node *root_node;
} ListStack;

int list_stack_init(ListStack *stack) {

  stack->root_node = node_init();
  return 0;
}

int list_stack_is_empty(ListStack *stack) { return stack->root_node == NULL; }

int list_stack_push(ListStack *stack, int value) {
  if (stack->root_node == NULL) {
    return 1;
  }

  stack->root_node = node_append_with_value(stack->root_node, value);

  return 0;
}

int list_stack_pop(ListStack *stack, int *result) {

  if (stack->root_node == NULL) {
    return 1;
  }

  Node *last_node = stack->root_node, *next_to_last_node = stack->root_node;
  for (; last_node->next != NULL; last_node = last_node->next) {
    next_to_last_node = last_node;
  }

  *result = last_node->data;

  free(last_node);
  next_to_last_node->next = NULL;

  return 0;
}

#endif
