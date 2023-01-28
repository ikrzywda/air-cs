#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

typedef enum {
  UNDEFINED,
  VALUE,
  ADD = '+',
  SUB = '-',
  MULT = '*',
  DIV = '/',
} TokenType;

typedef struct {
  TokenType type;
  int value;
} Token;

void print_token(Token *token);

#endif
