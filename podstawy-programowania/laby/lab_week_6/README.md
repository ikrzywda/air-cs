# Igor Krzywda (275480)

## Specyfikacja

* Wejście: wyrazenie rpn z `stdin`
* Wyjście: ewaluacja wyrazenie na `stdout`

## Czytanie wejścia

```c
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
```


## Token


```c
typedef enum {
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
```

## Lexer

```c
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
```

## Parser

```c
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
```

## Evaluator

* **Operacje binarne**

```c
int eval_binop(Stack *stack, int *result) {
  Token current_token;
  int result_1, result_2;
  stack_pop(stack, &current_token);

  if (current_token.type == VALUE) {
    return 1;
  }

  if (eval_term(stack, &result_1) || eval_term(stack, &result_2)) {
    return 1;
  }

  switch (current_token.type) {
  case ADD: {
    *result = result_1 + result_2;
    break;
  }
  case SUB: {
    *result = result_1 - result_2;
    break;
  }
  case MULT: {
    *result = result_1 * result_2;
    break;
  }
  case DIV: {
    if (result_2 == 0) {
      return 1;
    }
    *result = result_1 / result_2;
    break;
  }
  }

  return 0;
}
```

* **terma**

```c
int eval_term(Stack *stack, int *result) {
  Token current_token;
  stack_pop(stack, &current_token);

  print_token(&current_token);

  if (current_token.type == VALUE) {
    *result = current_token.value;
    return 0;
  }

  return eval_binop(stack, result);
}
```


### Testy
