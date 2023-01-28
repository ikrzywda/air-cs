#include "rpn-calculator/evaluator.h"
#include "rpn-calculator/lexer.h"
#include "rpn-calculator/parser.h"
#include "rpn-calculator/stack.h"
#include "rpn-calculator/token.h"

int main() {
  Stack stack;
  stack_init(&stack);
  char input[100], c;
  int i = 0, result;

  while (1) {
    while ((c = getchar()) != '\n') {
      input[i++] = c;
    }

    input[i] = '\0';
    parse_input(input, &stack);

    stack_print(&stack);
    eval_binop(&stack, &result);
    printf("%d", result);
    i = 0;
    putchar('\n');
  }
}
