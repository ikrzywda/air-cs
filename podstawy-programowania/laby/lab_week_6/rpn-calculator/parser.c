#include "parser.h"

int parse_input(char *input, Stack *stack) {
  char *current_token;
  Token parsed_token;
  char *delim = " \n";

  current_token = strtok(input, delim);

  while (current_token != NULL) {
    if (get_token(current_token, &parsed_token)) {
      return 1;
    }
    stack_push(stack, &parsed_token);
    current_token = strtok(NULL, delim);
  }
}
