#include <stdio.h>

#include "linked_list.h"
#include "stack_dynamic_array.h"
#include "stack_linked_list.h"

void print_list_with_comment(Node *root, char *comment) {
  printf("%s:\n[ ", comment);
  for (Node *temp = root; temp != NULL; ) {
    printf("%d ", temp->data, temp->next);
    temp = temp->next;
  }
  printf("]\n\n");
}

void print_stack_with_comment(ArrayStack *stack, char *comment) {
  
  printf("%s:\n", comment);

  printf("SIZE: %d\n", stack->size);
  printf("CONTENTS: ");
  for (int i = 0; i <= stack->index; ++i) {
    printf("%d ", stack->contents[i]);
  }

  printf("\n");
}


void show_off_list() {
  Node *root = node_init_with_value(2137);
  print_list_with_comment(root, "init");

  root = node_append_with_value(root, 37);
  root = node_append_with_value(root, 73);
  root = node_append_with_value(root, 12);
  print_list_with_comment(root, "appended");

  root = node_prepend_with_value(root, 21);
  print_list_with_comment(root, "prepend");

  root = node_delete_first(root);
  print_list_with_comment(root, "delete first");

  Node *to_be_deleted_after = root->next;

  root = node_delete_next(root, to_be_deleted_after);
  print_list_with_comment(root, "deletion after 37");
}

void show_off_stack() {
  ArrayStack stack;
  array_stack_init(&stack);

  array_stack_push(&stack, 1);
  print_stack_with_comment(&stack, "pushed value");

  for (int i = 0; i < 31; ++i) {
    array_stack_push(&stack, i + 2);
  }
  print_stack_with_comment(&stack, "reallocation");

}

int main() {
  show_off_list();
  show_off_stack();
  return 0;
}
