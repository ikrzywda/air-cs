#include "rpn-calculator/evaluator.h"
#include "rpn-calculator/lexer.h"
#include "rpn-calculator/parser.h"
#include "rpn-calculator/stack.h"
#include "rpn-calculator/token.h"

int main() {
  Stack stack;
  stack_init(&stack);
  int exit_flag = 0;
  char input[100], c;
  int i = 0, result;

  while (!exit_flag) {

    while ((c = getchar()) != '\n') {
      if (c == 'q') {
        exit_flag = 1;
      }
      
      input[i++] = c;
    }

    if (exit_flag) {
      break;
    }

    input[i] = '\0';
    parse_input(input, &stack);

    eval_binop(&stack, &result);
    printf("RESULT: %d", result);
    i = 0;
    putchar('\n');
  }

  free(stack.contents);
  return 0;
}
