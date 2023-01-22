#ifndef _STACK_DYNAMIC_ARRAY_H
#define _STACK_DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define ARR_STACK_STARTING_SIZE 8

typedef struct {
  int *contents;
  int index;
  int size;
} ArrayStack;

int array_stack_init(ArrayStack *stack) {

  stack->index = -1;
  stack->size = 8;

  printf("%d", sizeof(int) * 8);
  stack->contents = (int*)malloc(sizeof(int) * 8);

  return 0;
}

int array_stack_is_empty(ArrayStack *stack) {
  assert(stack->contents != NULL);
  
  return stack->index < 0;
}

int array_stack_push(ArrayStack *stack, int value) {  
  int new_size;

  if (stack->index >= stack->size - 2) {
    new_size = stack->size * 2;
    printf("REALLOC %d", new_size);

    stack->contents = (int*)realloc(stack->contents, new_size);

    printf("%p %d\n", stack->contents, new_size);
    stack->size = new_size;
  }

  printf("%d index %d value\n", stack->index, value);
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
