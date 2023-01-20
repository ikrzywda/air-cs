#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "linked_list.h"

#define STARTING_SIZE 256
#define STACK_EXIT_CODE INT_MAX

typedef struct {
  Node *root_node, *current_node;
} Stack;



