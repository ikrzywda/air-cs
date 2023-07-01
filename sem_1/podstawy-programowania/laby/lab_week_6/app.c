#include "rpn-calculator/rpn.h"

int main() {
  Stack stack;
  stack_init(&stack);
  int exit_flag = 0;
  char input[100], c;
  int i = 0, result = 0;

  while (!exit_flag) {
    printf(">>> ");
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

    if (!eval_binop(&stack, &result)) {
      printf("%d", result);
    }
    i = 0;
    putchar('\n');
  }

  free(stack.contents);
  return 0;
}
