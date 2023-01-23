#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BNode BNode;

typedef struct BNode {
  int data;
  BNode *next;
  BNode *prev;
} BNode;

BNode *bnode_init() {
  BNode *node = (BNode *)malloc(sizeof(BNode));
  node->data = 0;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

BNode *bnode_init_with_value(int value) {
  BNode *node = bnode_init();
  node->data = value;
  return node;
}

BNode *bnode_prepend(BNode *root, BNode *new_node) {
  root->prev = new_node;
  new_node->next = root;
  return new_node;
}

BNode *bnode_prepend_with_value(BNode *node, int value) {
  BNode *new_node = bnode_init_with_value(value);
  return bnode_prepend(node, new_node);
}

BNode *bnode_append(BNode *root, BNode *new_node) {
  BNode *last_node = root;

  for (; last_node->next != NULL;) {
    last_node = last_node->next;
  }

  last_node->next = new_node;
  new_node->prev = last_node;
  return root;
}

BNode *bnode_append_with_value(BNode *node, int value) {
  BNode *new_node = bnode_init_with_value(value);
  return bnode_append(node, new_node);
}

BNode *bnode_delete_first(BNode *root) {
  if (root == NULL) {
    return root;
  }

  if (root->next == NULL) {
    free(root);
    return NULL;
  }

  BNode *new_root = root->next;
  new_root->prev = NULL;
  free(root);

  return new_root;
}

BNode *bnode_delete_last(BNode *root) {

  if (root == NULL) {
    return root;
  }

  BNode *last_node = root, *next_to_last_node = root;
  for (; last_node->next != NULL; last_node = last_node->next) {
    next_to_last_node = last_node;
  }

  free(last_node);
  next_to_last_node->next = NULL;

  return root;
}

BNode *bnode_delete_next(BNode *root, BNode *node) {
  if (root == NULL || node == NULL) {
    return root;
  }

  BNode *rest, *target_node = node->next;
  if (target_node == NULL) {
    return root;
  }

  rest = target_node->next;

  free(target_node);
  node->next = rest;
  rest->prev = node;
  return root;
}

BNode *bnode_delete(BNode *root, BNode *node) {
  if (root == NULL || node == NULL) {
    return root;
  }

  BNode *temp_tail = root, *rest = node->next;
  for (; temp_tail->next != node; temp_tail = temp_tail->next)
    ;

  temp_tail->next = rest;
  rest->prev = temp_tail;
  free(node);

  return root;
}

int free_blist(BNode *root) {
  while ((root = bnode_delete_first(root)) != NULL) {
  }
  return 0;
}

#endif
