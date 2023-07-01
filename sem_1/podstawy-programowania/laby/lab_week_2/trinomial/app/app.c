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