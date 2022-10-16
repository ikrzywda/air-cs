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