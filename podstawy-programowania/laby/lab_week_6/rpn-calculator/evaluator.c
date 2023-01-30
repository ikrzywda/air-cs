#include "evaluator.h"

int eval_binop(Stack *stack, int *result) {
  Token current_token;
  int result_1, result_2;
  if (stack_pop(stack, &current_token)) {
    return 1;
  }

  if (current_token.type == VALUE) {
    printf("ERROR: Unexpected token: value\n");
    return 1;
  }

  if (eval_term(stack, &result_1) || eval_term(stack, &result_2)) {
    printf("ERROR: Unexpected end of input\n");
    return 1;
  }

  switch (current_token.type) {
  case ADD: {
    *result = result_2 + result_1;
    break;
  }
  case SUB: {
    *result = result_2 - result_1;
    break;
  }
  case MULT: {
    *result = result_2 * result_1;
    break;
  }
  case DIV: {
    if (result_1 == 0) {
      return 1;
    }
    *result = result_2 / result_1;
    break;
  }
  default:
    return 1;
  }

  return 0;
}

int eval_term(Stack *stack, int *result) {
  Token current_token;
  if (stack_peek(stack, &current_token)) {
    return 1;
  }

  if (current_token.type == VALUE) {
    *result = current_token.value;
    stack_pop(stack, &current_token);
    return 0;
  }

  return eval_binop(stack, result);
}
