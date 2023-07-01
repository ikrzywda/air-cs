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
