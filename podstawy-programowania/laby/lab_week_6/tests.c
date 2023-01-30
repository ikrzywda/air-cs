#include "rpn-calculator/rpn.h"
#include <assert.h>

int test_lexer() {
  Lexer lexer;
  char *input = "10 -10 + - * /";
  lexer_init_input(&lexer, input);

  int result_arr[6] = {10, -10, ADD, SUB, MULT, DIV};
  Token token;

  for (int i = 0; i < 2; ++i) {
    assert(get_next_token(&lexer, &token) == 0);
    assert(token.value == result_arr[i]);
    assert(token.type == VALUE);
  }

  for (int i = 2; i < 6; ++i) {
    assert(get_next_token(&lexer, &token) == 0);
    assert(token.type == result_arr[i]);
  }

  return 0;
}

int main() { test_lexer(); }
