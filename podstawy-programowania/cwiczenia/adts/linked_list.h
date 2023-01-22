#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

typedef struct Node {
  int data;
  Node *next; 
} Node;


Node *node_init() {
  Node *node = (Node*)malloc(sizeof(Node));
  node->next = NULL;
  return node;
}

Node *node_init_with_value(int value) {
  Node *node = node_init();
  node->data = value;
  return node;
}

Node *node_prepend(Node *root, Node *new_node) {
  new_node->next = root;
  return new_node;
}

Node *node_prepend_with_value(Node *node, int value) {
  Node *new_node = node_init_with_value(value);
  return node_prepend(node, new_node);
}

Node *node_append(Node *root, Node *new_node) {
  Node *last_node = root;

  for (; last_node->next != NULL; ) {
    last_node = last_node->next;
  }

  last_node->next = new_node;
  return root;
}

Node *node_append_with_value(Node *node, int value) {
  Node *new_node = node_init_with_value(value);
  return node_append(node, new_node);
}

Node *node_delete_first(Node *root) {
  if (root == NULL) {
    return root;
  }

  Node *new_root = root->next;
  free(root);

  return new_root;
}

Node *node_delete_last(Node *root) {

  if (root == NULL) {
    return root;
  }

  Node *last_node = root, *next_to_last_node = root;
  for (; last_node->next != NULL; last_node = last_node->next) {
    next_to_last_node = last_node;
  }

  free(last_node);
  next_to_last_node->next = NULL;

  return root;
}


Node *node_delete_next(Node *root, Node *node) {
  if (root == NULL || node == NULL) {
    return root;
  }

  Node *rest, *target_node = node->next;
  if (target_node == NULL) {
    return root;
  }

  rest = target_node->next;
  free(target_node);

  node->next = rest;
  return root;
}

Node *node_delete(Node *root, Node *node) {
  if (root == NULL || node == NULL) {
    return root;
  }

  Node *temp_tail = root, *rest = node->next;
  for (; temp_tail->next != node; temp_tail = temp_tail->next);

  temp_tail->next = rest;
  free(node);

  return root;
}

#endif
