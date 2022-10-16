#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int solution_count;
  char message[50];
  float results[4]; // [result, result, result, delta]
} TrinomialSolution;

void trinomial_results(TrinomialSolution *solution_ptr, float a, float b, float c)
{
  solution_ptr->solution_count = 0;
  float delta;

  if (!a)
  {
    if (b)
    {
      solution_ptr->results[0] = -c / b;
      solution_ptr->solution_count = 1;
    }
    else if (!c)
    {
      strcpy(solution_ptr->message, "Rozwiazaniem jest dowolne x");
      solution_ptr->solution_count = 0;
    }
    else
    {
      strcpy(solution_ptr->message, "Brak rozwiazan");
      solution_ptr->solution_count = 0;
    }
    return;
  }

  delta = pow(b, 2) - 4.0 * a * c;
  if (delta < 0)
  {
    strcpy(solution_ptr->message, "Brak rozwiazan");
    solution_ptr->solution_count = 0;
    solution_ptr->results[3] = delta;
  }
  else if (delta > 0)
    {
      solution_ptr->solution_count = 2;
      solution_ptr->results[0] = (-b - sqrt(delta)) / (2 * a);
      solution_ptr->results[1] = (-b + sqrt(delta)) / (2 * a);
    }
    else
    {
      solution_ptr->results[0] = solution_ptr->results[1] =
          (-b + sqrt(delta)) / (2 * a);
      solution_ptr->solution_count = 2;
    }
  }

void print_solution(TrinomialSolution *solution)
{
  printf("RESULTS:\n%s\n", solution->message);
  for (int i = 0; i < solution->solution_count; ++i)
  {
    printf("%f ", solution->results[i]);
  }
  printf("\n");
}
