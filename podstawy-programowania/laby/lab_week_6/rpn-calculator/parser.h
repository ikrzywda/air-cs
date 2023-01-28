#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "stack.h"
#include "token.h"

int parse_input(char *input, Stack *stack);

#endif
