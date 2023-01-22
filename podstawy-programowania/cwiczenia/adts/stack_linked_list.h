#ifndef _STACK_LIST_H
#define _STACK_LIST_H

#include <stdlib.h>
#include <assert.h>

#include "linked_list.h"

#define STARTING_SIZE 256
#define STACK_EXIT_CODE INT_MAX

typedef struct {
  Node *root_node;
  Node *head_node;
} ListStack;


int list_stack_init(ListStack *stack) {
  if (stack->root_node != NULL) {
    return 1;
  }

  stack->root_node = node_init();
  stack->head_node = stack->root_node;
  return 0;
}

int list_stack_is_empty(ListStack *stack) {
  return stack->root_node == NULL;
}

int list_stack_push(ListStack *stack, int value) {  
  if (stack->root_node == NULL) {
    return 1;
  }
  
  node_append_with_value(stack->root_node, value);
  stack->head_node = stack->head_node->next;

  return 0;
}

int list_stack_pop(ListStack *stack, int *result) {

  if (list_stack_is_empty(stack)) {
    return 0;
  }

  *result = stack->head_node->data;

  Node *delete_node = NULL, *temp_tail = stack->root_node;
  for (; temp_tail->next == stack->head_node; temp_tail = temp_tail->next);
  
  free(stack->head_node);
  stack->head_node = temp_tail;

  return 0;
}

#endif
