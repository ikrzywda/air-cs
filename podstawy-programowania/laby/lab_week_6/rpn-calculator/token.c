#include "token.h"

void print_token(Token *token) {
  if (token->type == UNDEFINED) {
    printf("UNDEFINED");
  } else if (token->type == VALUE) {
    printf("TOKEN: %d", token->value);
  } else if (token->type) {
    printf("TOKEN: %c", token->type);
  }
  putchar('\n');
}
