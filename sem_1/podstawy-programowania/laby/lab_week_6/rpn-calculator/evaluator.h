#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "stack.h"
#include "token.h"

int eval_binop(Stack *stack, int *result);
int eval_term(Stack *stack, int *result);

#endif
