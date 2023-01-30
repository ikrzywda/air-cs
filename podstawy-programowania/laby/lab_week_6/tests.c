#include <assert.h>

#include "rpn-calculator/rpn.h"

void test_lexer() {
  char *input[6] = {"10", "-10", "+", "-", "*", "/"};

  int result_arr[6] = {10, -10, ADD, SUB, MULT, DIV};
  Token token;

  for (int i = 0; i < 2; ++i) {
    assert(get_token(input[i], &token) == 0);
    assert(token.value == result_arr[i]);
    assert(token.type == VALUE);
  }

  for (int i = 2; i < 6; ++i) {
    assert(get_token(input[i], &token) == 0);
    assert(token.type == result_arr[i]);
  }
}

void test_parser_push_on_stack() {
  char input[100] = "10 -10 + - * /";
  Stack stack;
  int result_arr[6] = {DIV, MULT, SUB, ADD, VALUE, VALUE};
  Token token;

  assert(!stack_init(&stack));
  assert(!parse_input(input, &stack));

  for (int i = 0; i < 6; ++i) {
    assert(!stack_pop(&stack, &token));
    assert(token.type == result_arr[i]);
  }
  assert(stack_is_empty(&stack));

  free(stack.contents);
}

void test_evaluator_binops() {
  char input[4][100] = {"3 3 +", "3 3 -", "3 3 *", "3 3 /"};

  int result_arr[4] = {6, 0, 9, 1}, result;

  Stack stack;
  assert(!stack_init(&stack));

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(!eval_binop(&stack, &result));
    assert(result == result_arr[i]);
  }
}

void test_evaluator_nested_binops() {
  char input[4][100] = {
      "1 2 * 3 * 4 * 5 *",    
      "1 2 + 3 + 4 + 5 +",    
      "16 2 / 2 / 2 / 2 /",  
      "5 1 - 1 - 1 - 1 - 1 -" 
  };

  int result_arr[4] = {120, 15, 1, 0}, result;

  Stack stack;
  assert(!stack_init(&stack));

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(!eval_binop(&stack, &result));
    assert(result == result_arr[i]);
  }
}

void test_evaluator_errors() {
  char input[4][100] = {
      "1 + +",    
      "1 2",    
      "+",  
      "2 2 2" 
  };

  Stack stack;
  assert(!stack_init(&stack));
  int result;

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(eval_binop(&stack, &result));
  }
}

int main() {
  test_lexer();
  test_parser_push_on_stack();
  test_evaluator_binops();
  test_evaluator_nested_binops();
  test_evaluator_errors();
}
