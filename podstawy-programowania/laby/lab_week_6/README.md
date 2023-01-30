# Igor Krzywda (275480)

## Specyfikacja

* Wejście: wyrazenie rpn z `stdin`
* Wyjście: ewaluacja wyrazenia na `stdout`

## Analiza leksykalna

### Tokeny

Tokeny są strukturami trzymającymi typ i wartośc - są typem wyjsciowym analizy
leksykalnej - do wartosci enumeracji dla operacji sa przypisane terminale

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

### Lexer

Funkcja `get_token` przyjmuje ciąg znaków i referencję do obiektu `Token` i
zapisuje odpowiedni token przekazanemu obiektowi na sukces.

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


## Parsowanie 

### Stos (IR)

Stos jest zaimplementowany jako tablica dynamiczna referencji do `Tokenów` - 
implementacja metod w `rpn-calculator/stack.c`

```c
typedef struct {
  Token *contents;
  int index;
  int size;
} Stack;
```

```c
int stack_init(Stack *stack) {

  stack->index = -1;
  stack->size = 8;

  stack->contents = malloc(sizeof(Token) * 8);

  return 0;
}
```

### Parser

Jako parsowanie przyjmuję tworzenie reprezentacji pośredniej (Intermediate Representation) - 
w tym przypadku stos - analiza syntaktyczna jest wykonywana w następnej fazie

Funkcja bierze ciąg znaków zawierające pełne wyrazenie i uzywając `strtok` iteruje
po wyrazach oddzielonych spacją, przekazuje ją do lexera i wrzuca token na stos


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

## Ewaluacja IR

Wyrazenia `rpn` ewaluuję według następującej gramatyki (jest to gramatyka,
którą widzi ewaluator jak tokeny są zdejmowane ze stosu)

```bnf
binop  ::=   operator term term
term   ::=   number | binop
number ::=   '-'? digit
digit  ::=   '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
```

Wartosci posrednie zachowywane sa w stosie wywolan rekurencyjnych w zmiennych
`result_1`, `result_2`. W ewaluacji operacji binarnej zapisuje token ze szczytu stosu i 
aplikuję operację pierwszego tokena na wartosci posrednie.

Przy ewaluacji `term` sprawdzam szczyt stosu (metoda `stack_peek` nie zdejmuje tokena ze stosu)
i jesli jest to wartosc, to zwracam tę wartosc i zdejmuje token ze stosu, w.p.p wykonuje ewaluacje
operacji binarnej.

```c
int eval_binop(Stack *stack, int *result) {
  Token current_token;
  int result_1, result_2;
  if (stack_pop(stack, &current_token)) {
    return 1;
  }

  if (current_token.type == VALUE) {
    printf("ERROR: Unexpected token: value\n");
    return 1;
  }

  if (eval_term(stack, &result_1) || eval_term(stack, &result_2)) {
    printf("ERROR: Unexpected end of input\n");
    return 1;
  }

  switch (current_token.type) {
  case ADD: {
    *result = result_2 + result_1;
    break;
  }
  case SUB: {
    *result = result_2 - result_1;
    break;
  }
  case MULT: {
    *result = result_2 * result_1;
    break;
  }
  case DIV: {
    if (result_1 == 0) {
      return 1;
    }
    *result = result_2 / result_1;
    break;
  }
  default:
    return 1;
  }

  return 0;
}

int eval_term(Stack *stack, int *result) {
  Token current_token;
  if (stack_peek(stack, &current_token)) {
    return 1;
  }

  if (current_token.type == VALUE) {
    *result = current_token.value;
    stack_pop(stack, &current_token);
    return 0;
  }

  return eval_binop(stack, result);
}
```

## Driver code

Jest to prosty REPL z gracious exit dla dealokacji pamięci

```c
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
```

## Testy Jednostkowe

Aby przetestowac program napisałem testy jednostkowe testujące
kazdy etap ewaluacji wyrazenia rpn

### Tokenizacja

Sprawdzam, czy tokeny są dobrze rozpoznawane

```c
void test_lexer() {
  char *input[6] = {"10", "-10", "+", "-", "*", "/"};

  int result_arr[6] = {10, -10, ADD, SUB, MULT, DIV};
  Token token;

  for (int i = 0; i < 2; ++i) {
    assert(get_token(input[i], &token) == 0);
    assert(token.value == result_arr[i]);
    assert(token.type == VALUE);
  }

  for (int i = 2; i < 6; ++i) {
    assert(get_token(input[i], &token) == 0);
    assert(token.type == result_arr[i]);
  }
}
```

### Parsowanie

Sprawdzam, czy IR (stos) jest poprawnie konstruowany - stos powinien miec wysokosc
6 i zawierac odwrotnosc wejscia

```c
void test_parser_push_on_stack() {
  char input[100] = "10 -10 + - * /";
  Stack stack;
  int result_arr[6] = {DIV, MULT, SUB, ADD, VALUE, VALUE};
  Token token;

  assert(!stack_init(&stack));
  assert(!parse_input(input, &stack));

  for (int i = 0; i < 6; ++i) {
    assert(!stack_pop(&stack, &token));
    assert(token.type == result_arr[i]);
  }
  assert(stack_is_empty(&stack));

  free(stack.contents);
}
```

### Ewaluacje wyrazen

* **podstawowe wyrazenia binarne**

Sprawdzam czy podstawowe wyrazenia binarne są poprawnie ewaluowane - dodawanie,
odejmowanie, mnozenie i dzielenie (dodatkowo sprawdzenie walidacji dzielenia przez 0)

```c
void test_evaluator_binops() {
  char input[5][100] = {"3 3 +", "3 3 -", "3 3 *", "3 3 /", "2 0 /"};

  int result_arr[4] = {6, 0, 9, 1}, result;

  Stack stack;
  assert(!stack_init(&stack));

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(!eval_binop(&stack, &result));
    assert(result == result_arr[i]);
  }

  assert(!parse_input(input[4], &stack));
  assert(eval_binop(&stack, &result)); 

  free(stack.contents);
}
```

* **zagniezdzone wyrazenia binarne**

Sprawdzam, czy zagniezdzone wyrazenia binarne są poprawnie ewaluowane

```c
void test_evaluator_nested_binops() {
  char input[4][100] = {
      "1 2 * 3 * 4 * 5 *",    
      "1 2 + 3 + 4 + 5 +",    
      "16 2 / 2 / 2 / 2 /",  
      "5 1 - 1 - 1 - 1 - 1 -" 
  };

  int result_arr[4] = {120, 15, 1, 0}, result;

  Stack stack;
  assert(!stack_init(&stack));

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(!eval_binop(&stack, &result));
    assert(result == result_arr[i]);
  }
  free(stack.contents);
}
```

* **walidowanie blędow w skladni**

```c

void test_evaluator_errors() {
  char input[4][100] = {
      "1 + +",    
      "1 2",    
      "+",  
      "2 2 2" 
  };

  Stack stack;
  assert(!stack_init(&stack));
  int result;

  for (int i = 0; i < 4; ++i) {
    assert(!parse_input(input[i], &stack));
    assert(eval_binop(&stack, &result));
  }
  free(stack.contents);
}
```
