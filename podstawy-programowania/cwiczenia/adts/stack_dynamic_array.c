#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define STARTING_SIZE 256
#define STACK_EXIT_CODE INT_MAX

typedef struct {
  int *contents;
  int index, resize_factor;
  size_t size;
} Stack;

int init(Stack *stack) {
  assert(stack->contents == NULL);

  stack->index = -1;
  stack->resize_factor = 2;
  stack->size = STARTING_SIZE;

  stack->contents = malloc(sizeof(int) * STARTING_SIZE);

  return 0;
}

int is_empty(Stack *stack) {
  assert(stack->contents != NULL);
  
  return stack->index < 0;
}

int push(Stack *stack, int value) {
  assert(stack->contents != NULL);

  int new_size;

  if (stack->index >= stack->size - 1) {
    new_size = stack->size * stack->resize_factor;
    stack->resize_factor *= 2;

    realloc(stack->contents, new_size);

    stack->size = new_size;
  }

  ++stack->index;
  stack->contents[stack->index] = value;

  return value;
}

int pop(Stack *stack) {
  assert(stack->contents != NULL); 

  if (is_empty(stack)) {
    return STACK_EXIT_CODE;
  }

  int value = stack->contents[stack->index];
  --stack->index;

  return value;
}

int main() {
  return 0;
}


