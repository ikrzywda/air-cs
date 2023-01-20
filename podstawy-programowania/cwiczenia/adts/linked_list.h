#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

typedef struct Node {
  int data;
  Node *next; 
} Node;


Node *node_init() {
  Node *node = (Node*)malloc(sizeof(Node));
  return node;
}

Node *node_init_with_value(int value) {
  Node *node = (Node*)malloc(sizeof(Node));
  node->data = value;
  return node;
}

Node *node_prepend(Node *node, Node *new_node) {
  new_node->next = new_node;
  return new_node;
}

Node *node_prepend_with_value(Node *node, int value) {
  Node *new_node = node_init_with_value(value);
  return node_prepend(node, new_node);
}

Node *node_append(Node *node, Node *new_node) {
  node->next = new_node;
  return new_node;
}

Node *node_append_with_value(Node *node, int value) {
  Node *new_node = node_init_with_value(value);
  return node_append(node, new_node);
}
