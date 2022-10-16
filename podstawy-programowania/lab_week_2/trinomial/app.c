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

  TrinomialSolution solution;
  trinomial_results(&solution, a,b,c);
  print_solution(&solution);

  return 0;
}