#ifndef _STACK
#define _STACK

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

#define ARR_STACK_STARTING_SIZE 8

typedef struct {
  Token *contents;
  int index;
  int size;
} Stack;

int stack_init(Stack *stack);
int stack_is_empty(Stack *stack);
int stack_push(Stack *stack, Token *value);
int stack_pop(Stack *stack, Token *result);
int stack_peek(Stack *stack, Token *result);
void stack_print(Stack *stack);

#endif
