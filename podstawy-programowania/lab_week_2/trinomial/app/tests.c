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
