# Trójmian

>## Autor: Igor Krzywda (275480)
>### Data Wykonania: 16.10.22

## Kod źródłowy

Kod został zmodyfikowany na rzecz możliwości napisana zautomatyzowanych testów:

* zwracanie wyników w postaci wskaźnika do obiektu opisującego rozwiązanie
  * typ równania (liniowe, kwadratowe)
  * opis w przypadku braku rozwiązań
  * liczba rozwiązań
  * rozwiązania równania i opcjonalnie delta
* rozdzielenie funkcjonalności liczenia i drukowania do oddzielnego modułu


* `trinomial.h`

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { LINEAR, QUADRATIC } FunctionType;

typedef struct {
  FunctionType function_type;
  int solution_count;
  char message[50];
  float results[3];  // [result, result, delta]
} TrinomialSolution;

TrinomialSolution *trinomial_results(float a, float b, float c) {
  TrinomialSolution *solution_ptr = malloc(sizeof(TrinomialSolution));
  solution_ptr->solution_count = 0;
  float delta;

  if (!a) {
    if (b) {
      solution_ptr->results[0] = -c / b;
      solution_ptr->solution_count = 1;
    }
    if (!b && !c) {
      strcpy(solution_ptr->message, "Rozwiazaniem jest dowolne x");
      solution_ptr->solution_count = 0;
    }
    if (!b && c) {
      strcpy(solution_ptr->message, "Brak rozwiazan");
      solution_ptr->solution_count = 0;
    }
    solution_ptr->function_type = LINEAR;
    return solution_ptr;
  }

  delta = pow(b, 2) - 4.0 * a * c;
  if (delta < 0) {
    strcpy(solution_ptr->message, "Brak rozwiazan");
    solution_ptr->solution_count = 0;
    solution_ptr->results[2] = delta;
  } else if (delta > 0) {
    solution_ptr->solution_count = 2;
    solution_ptr->results[0] = (-b - sqrt(delta)) / (2 * a);
    solution_ptr->results[1] = (-b + sqrt(delta)) / (2 * a);
    solution_ptr->results[2] = delta;
  } else {
    solution_ptr->results[0] = solution_ptr->results[1] = (-b) / (2 * a);
    solution_ptr->results[2] = delta;
    solution_ptr->solution_count = 2;
  }
  solution_ptr->function_type = QUADRATIC;
  return solution_ptr;
}

void print_solution(TrinomialSolution *solution) {
  printf("\nSOLUTIONS: ");
  if (solution->solution_count) {
    for (int i = 0; i < solution->solution_count; ++i) {
      printf("%f ", solution->results[i]);
    }
  } else {
    printf("RESULTS:\n%s", solution->message);
  }

  if (solution->function_type == QUADRATIC) {
    printf("\nFUNCTION_TYPE: quadratic");
    printf("\nDELTA = %f", solution->results[2]);
  } else {
    printf("\nFUNCTION_TYPE: linear\n");
  }
}
```

* `app.c`

```c
#include "trinomial.h"

int main() {
  float a, b, c;

  printf("This program computes roots of trinomial in a form of");
  printf("\n  a(x)+b(x)+c = 0");
  printf("\nEnter a: ");
  scanf("%f", &a);
  printf("Enter b: ");
  scanf("%f", &b);
  printf("Enter c: ");
  scanf("%f", &c);

  TrinomialSolution *solution = trinomial_results(a, b, c);
  print_solution(solution);

  return 0;
}
```


## Testy

Do testów używane są asercje - nie jest to najlepsze rozwiązanie, ponieważ
asercje terminują program na fałszywe wyrażenie zatem wiadomo tylko o pierwszym
failującym teście. Lepszym rozwiązaniem byłby framework pozwalający na logowanie
wyników.

## Struktura testów

* *setup* : stworzenie nowej instancji obiektu `TrinomialSolution` z `trinomial_solutions`
* *testy* : sprawdzanie wyników z wcześniej obliczonymi rezultatami
* *teardown* : dealokowanie testowego obiektu

Testy pokrywają każdy przypadek w algorytmie - jako opis służą nazwy funkcji a jako


## Kod

* `tests.c`

```c
#include <assert.h>

#include "trinomial.h"

void test_trinomial_results_linear_function_with_solutions() {
  TrinomialSolution* solution = trinomial_results(0, 3, 15);

  assert(solution->solution_count == 1);
  assert(solution->results[0] == -5);
  assert(solution->function_type == LINEAR);

  free(solution);
}

void test_trinomial_results_linear_function_any_x_as_solution() {
  TrinomialSolution* solution = trinomial_results(0, 0, 0);
  assert(!solution->solution_count);

  trinomial_results(0, 0, 0);
  assert(!solution->solution_count);
  assert(solution->function_type == LINEAR);

  free(solution);
}

void test_trinomial_results_linear_function_with_no_solutions() {
  TrinomialSolution* solution = trinomial_results(0, 0, 15);
  assert(!solution->solution_count);

  trinomial_results(0, 0, 15);
  assert(!solution->solution_count);
  assert(solution->function_type == LINEAR);

  free(solution);
}

void test_trinomial_results_quadratic_function_no_solutions() {
  TrinomialSolution* solution = trinomial_results(1, 1, 2);
  assert(!solution->solution_count);
  assert(solution->results[2] == -7);
  assert(solution->function_type == QUADRATIC);

  free(solution);
}

void test_trinomial_results_quadratic_function_two_solutions() {
  TrinomialSolution* solution = trinomial_results(1, 2, 1);

  assert(solution->solution_count == 2);
  assert(solution->results[0] == -1);
  assert(solution->results[1] == -1);
  assert(solution->results[2] == 0);
  assert(solution->function_type == QUADRATIC);

  free(solution);
}

void test_trinomial_results_quadratic_function_double_root() {
  TrinomialSolution* solution = trinomial_results(1, 8, 15);

  assert(solution->solution_count == 2);
  assert(solution->results[0] == -5);
  assert(solution->results[1] == -3);
  assert(solution->results[2] == 4);
  assert(solution->function_type == QUADRATIC);

  free(solution);
}

int main() {
  test_trinomial_results_linear_function_with_solutions();
  test_trinomial_results_linear_function_any_x_as_solution();
  test_trinomial_results_linear_function_with_no_solutions();
  test_trinomial_results_quadratic_function_two_solutions();
  test_trinomial_results_quadratic_function_double_root();
}
```

* `./run_tests.sh`

```bash
#!/bin/bash

echo "COMPILING TESTS..."
gcc -std=c99 -pedantic -Wall app/tests.c -lm -o tests

echo "RUNNING TESTS..."
./tests

rm tests
```

## Wyniki
 
Na wszystkich dostępnych maszynach (diablo (gcc), penamint (gcc), prywatna maszyna (clang)) 
testy przeszły bez wyrzucania błędów.
