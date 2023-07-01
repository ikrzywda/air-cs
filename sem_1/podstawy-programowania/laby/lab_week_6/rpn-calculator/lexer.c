#include "lexer.h"

int get_token(char *str, Token *token) {
  int value;

  if (!(*str)) {
    return 1;
  }

  if (sscanf(str, "%d", &value)) {
    token->type = VALUE;
    token->value = value;
    return 0;
  }

  switch (*str) {
  case ADD: {
    token->type = ADD;
    break;
  }
  case SUB: {
    token->type = SUB;
    break;
  }
  case MULT: {
    token->type = MULT;
    break;
  }
  case DIV: {
    token->type = DIV;
    break;
  }
  default: {
    return 1;
  }
  }

  return 0;
}
