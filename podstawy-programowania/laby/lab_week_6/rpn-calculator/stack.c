#include "stack.h"

int stack_init(Stack *stack) {

  stack->index = -1;
  stack->size = 8;

  stack->contents = malloc(sizeof(Token) * 8);

  return 0;
}

int stack_is_empty(Stack *stack) {
  assert(stack->contents != NULL);

  return stack->index < 0;
}

int stack_push(Stack *stack, Token *token) {
  int new_size, *reallocated_arr;

  if (stack->index >= stack->size - 2) {
    stack->size *= 2;

    reallocated_arr =
        (Token *)realloc(stack->contents, stack->size * sizeof(Token));
    if (reallocated_arr == NULL) {
      free(stack->contents);
      exit(1);
    }

    stack->contents = reallocated_arr;
  }

  stack->index++;
  stack->contents[stack->index] = *token;

  return 0;
}

int stack_pop(Stack *stack, Token *result) {
  assert(stack->contents != NULL);

  if (stack_is_empty(stack)) {
    return 1;
  }

  *result = stack->contents[stack->index];
  --stack->index;

  return 0;
}

void stack_print(Stack *stack) {
  for (int i = 0; i <= stack->index; ++i) {
    print_token(&stack->contents[i]);
  }
}
