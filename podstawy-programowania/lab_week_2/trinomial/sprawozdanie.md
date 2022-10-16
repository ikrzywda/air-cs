># Trójmian
>## Autor: Igor Krzywda
>### Data Wykonania: 16.10.22

## Kod źródłowy
Kod został zmodyfikowany na rzecz możliwości napisana zautomatyzowanych testów. 

* `trinomial.h`

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int solution_count;
  char message[50];
  float results[4];  // [result, result, result, delta]
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
    return solution_ptr;
  }

  delta = pow(b, 2) - 4.0 * a * c;
  if (delta < 0) {
    strcpy(solution_ptr->message, "Brak rozwiazan");
    solution_ptr->solution_count = 0;
    solution_ptr->results[3] = delta;
  } else if (delta > 0) {
    solution_ptr->solution_count = 2;
    solution_ptr->results[0] = (-b - sqrt(delta)) / (2 * a);
    solution_ptr->results[1] = (-b + sqrt(delta)) / (2 * a);
    solution_ptr->results[3] = delta;
  } else {
    solution_ptr->results[0] = solution_ptr->results[1] = (-b) / (2 * a);
    solution_ptr->results[3] = delta;
    solution_ptr->solution_count = 2;
  }
  return solution_ptr;
}

void print_solution(TrinomialSolution *solution) {
  printf("RESULTS:\n%s\n", solution->message);
  for (int i = 0; i < solution->solution_count; ++i) {
    printf("%f ", solution->results[i]);
  }
  printf("DELTA = %f", solution->results[3]);
  printf("\n");
}
```

* `app.c`

```c
#include "trinomial.h"

int main() {
  float a, b, c;

  printf("Program oblicza pierwiastki rownania w postaci\n");
  printf("     2\n");
  printf("  a x + b x +c =0\n");
  printf("Podaj wartosc a:");
  scanf("%f", &a);
  printf("Podaj wartosc b:");
  scanf("%f", &b);
  printf("Podaj wartosc c:");
  scanf("%f", &c);

  TrinomialSolution *solution = trinomial_results(a, b, c);
  print_solution(solution);
  free(solution);

  return 0;
}
```
* `tests.c`

```c
#include <assert.h>
#include <stdio.h>

#include "trinomial.h"

void test_trinomial_results_linear_function_with_solutions() {
  TrinomialSolution* solution = trinomial_results(0, 3, 15);

  assert(solution->solution_count == 1);
  assert(solution->results[0] == -5);

  free(solution);
}

void test_trinomial_results_linear_function_no_solutions() {
  TrinomialSolution* solution = trinomial_results(0, 0, 15);
  assert(!solution->solution_count);

  trinomial_results(0, 0, 0);
  assert(!solution->solution_count);

  free(solution);
}

void test_trinomial_results_quadratic_function_no_solutions() {
  TrinomialSolution* solution = trinomial_results(1, 1, 2);
  assert(!solution->solution_count);
  assert(solution->results[3] == -7);

  free(solution);
}

void test_trinomial_results_quadratic_function_with_solutions() {
  TrinomialSolution *solution_1, *solution_2;
  solution_1 = trinomial_results(1, 2, 1);
  assert(solution_1->solution_count == 2);
  assert(solution_1->results[0] == -1);
  assert(solution_1->results[1] == -1);
  assert(solution_1->results[3] == 0);

  solution_2 = trinomial_results(1, 8, 15);
  assert(solution_2->solution_count == 2);
  assert(solution_2->results[0] == -5);
  assert(solution_2->results[1] == -3);
  assert(solution_2->results[3] == 4);

  free(solution_1);
  free(solution_2);
}

int main() {
  test_trinomial_results_linear_function_with_solutions();
  test_trinomial_results_linear_function_no_solutions();
  test_trinomial_results_quadratic_function_no_solutions();
  test_trinomial_results_quadratic_function_with_solutions();
}
```

## Przeprowadzenie testów

>`./run_tests.sh`

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
 
Na wszystkich dostępnych maszynach (diablo, penamint, prywatny laptop) 
testy przeszły bez wyrzucania błędów.