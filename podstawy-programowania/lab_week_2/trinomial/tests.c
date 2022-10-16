#include "trinomial.h"
#include <assert.h>
#include <stdio.h>

void test_trinomial_results_linear_function_with_solutions() {
  TrinomialSolution solution;
  trinomial_results(&solution, 0,3,15);

  assert(solution.solution_count == 1);
  assert(solution.results[0] == -5);
}

void test_trinomial_results_linear_function_no_solutions() {
  TrinomialSolution solution;

  trinomial_results(&solution, 0,0,15);
  assert(!solution.solution_count);

  trinomial_results(&solution, 0,0,0);
  assert(!solution.solution_count);
}

void test_trinomial_results_quadratic_function_no_solutions() {
  TrinomialSolution solution;

  trinomial_results(&solution, 1,1,2);
  assert(!solution.solution_count);
  assert(solution.results[3] == -7);
}

void test_trinomial_results_quadratic_function_with_solutions() {
  TrinomialSolution solution;

  trinomial_results(&solution, 2,1,1);
  assert(solution.solution_count == 2);
  // assert(solution.results[0] == -7);
  // assert(solution.results[1] == -7);
  assert(solution.results[3] == 0);
}



int main() {
  test_trinomial_results_linear_function_with_solutions();
  test_trinomial_results_linear_function_no_solutions();
}