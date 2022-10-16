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
