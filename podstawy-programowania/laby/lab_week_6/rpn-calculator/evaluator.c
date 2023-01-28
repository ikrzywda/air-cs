#include "evaluator.h"

int eval_binop(Stack *stack, int *result) {
  Token current_token;
  int result_1, result_2;
  stack_pop(stack, &current_token);

  if (current_token.type == VALUE) {
    return 1;
  }

  if (eval_term(stack, &result_1) || eval_term(stack, &result_2)) {
    return 1;
  }

  switch (current_token.type) {
  case ADD: {
    *result = result_1 + result_2;
    break;
  }
  case SUB: {
    *result = result_1 - result_2;
    break;
  }
  case MULT: {
    *result = result_1 * result_2;
    break;
  }
  case DIV: {
    if (result_2 == 0) {
      return 1;
    }
    *result = result_1 / result_2;
    break;
  }
  }

  return 0;
}

int eval_term(Stack *stack, int *result) {
  Token current_token;
  stack_pop(stack, &current_token);

  printf("TERM: ");
  print_token(&current_token);

  if (current_token.type == VALUE) {
    *result = current_token.value;
    return 0;
  }

  return eval_binop(stack, result);
}
