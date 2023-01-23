#include <stdio.h>

#include "bidirectional_list.h"
#include "linked_list.h"
#include "stack_dynamic_array.h"
#include "stack_linked_list.h"

void print_blist_with_comment(BNode *root, char *comment) {
  printf("%s:\n[ ", comment);
  for (BNode *temp = root; temp != NULL;) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("]\n\n");
}

void print_list_with_comment(Node *root, char *comment) {
  printf("%s:\n[ ", comment);
  for (Node *temp = root; temp != NULL;) {
    printf("%d ", temp->data);
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

  free_list(root);
}

void show_off_blist() {
  BNode *root = bnode_init_with_value(2137);
  print_blist_with_comment(root, "init");

  root = bnode_append_with_value(root, 37);
  root = bnode_append_with_value(root, 73);
  root = bnode_append_with_value(root, 12);
  print_blist_with_comment(root, "appended");

  root = bnode_prepend_with_value(root, 21);
  print_blist_with_comment(root, "prepend");

  root = bnode_delete_first(root);
  print_blist_with_comment(root, "delete first");

  BNode *to_be_deleted_after = root->next;

  root = bnode_delete_next(root, to_be_deleted_after);
  print_blist_with_comment(root, "deletion after 37");

  free_blist(root);
}

void show_off_array_stack() {
  ArrayStack stack;
  int popped_value;
  array_stack_init(&stack);

  array_stack_push(&stack, 1);
  print_stack_with_comment(&stack, "pushed value");

  for (int i = 0; i < 31; ++i) {
    array_stack_push(&stack, i + 2);
  }
  print_stack_with_comment(&stack, "reallocation");

  printf("POPPING: \n");
  for (int i = 0; i < 16; ++i) {
    array_stack_pop(&stack, &popped_value);
    printf("%d ", popped_value);
  }
  print_stack_with_comment(&stack, "\nafter popping");

  free(stack.contents);
}

void show_off_list_stack() {
  ListStack stack;
  int popped_value;
  list_stack_init(&stack);

  list_stack_push(&stack, 1);

  for (int i = 0; i < 31; ++i) {
    list_stack_push(&stack, i + 2);
    ;
  }
  print_list_with_comment(stack.root_node, "reallocation");

  printf("POPPING: ");
  for (int i = 0; i < 16; ++i) {
    list_stack_pop(&stack, &popped_value);
    printf("%d ", popped_value);
  }
  print_list_with_comment(stack.root_node, "\nafter popping");

  free_list(stack.root_node);
}

int main() {
  show_off_blist();
  show_off_list();

  show_off_array_stack();
  show_off_list_stack();
  return 0;
}
