#ifndef _STACK_DYNAMIC_ARRAY_H
#define _STACK_DYNAMIC_ARRAY_H

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#define ARR_STACK_STARTING_SIZE 8

typedef struct {
  int *contents;
  int index;
  int size;
} ArrayStack;

int array_stack_init(ArrayStack *stack) {

  stack->index = -1;
  stack->size = 8;

  stack->contents = (int *)malloc(sizeof(int) * 8);

  return 0;
}

int array_stack_is_empty(ArrayStack *stack) {
  assert(stack->contents != NULL);

  return stack->index < 0;
}

int array_stack_push(ArrayStack *stack, int value) {
  int new_size, *reallocated_arr;

  if (stack->index >= stack->size - 2) {
    stack->size *= 2;

    reallocated_arr =
        (int *)realloc(stack->contents, stack->size * sizeof(int));
    if (reallocated_arr == NULL) {
      free(stack->contents);
      exit(1);
    } else {
      stack->contents = reallocated_arr;
    }

    stack->contents = reallocated_arr;
  }

  stack->index++;
  stack->contents[stack->index] = value;

  return 0;
}

int array_stack_pop(ArrayStack *stack, int *result) {
  assert(stack->contents != NULL);

  if (array_stack_is_empty(stack)) {
    return 0;
  }

  *result = stack->contents[stack->index];
  --stack->index;

  return 0;
}

#endif
