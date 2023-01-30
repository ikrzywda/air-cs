#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN

typedef enum {
  UNAME,
  ADRESS
} OrderingVariable;

typedef struct t_node t_node;
typedef struct t_node {
  t_node *parent;
  t_node *left;
  t_node *right;

  char *uname;
  char *address;

  OrderingVariable order_by;
} t_node;



int node_print(t_node *node) {
  if (node == NULL) {
    return 1;
  }
  printf("ADDRESS: %s\nUNAME: %s\n", node->address, node->uname);
  return 0;
}

t_node *node_init() {

  t_node *node = (t_node*)malloc(sizeof(t_node));
  
  if (!node) {
    return NULL;
  }

  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->address = (char*)malloc(sizeof(t_node));
  node->uname = (char*)malloc(sizeof(t_node));

  return node;
}

int node_push(t_node *node, char *address, char *uname) {
  char *cmp = node->order_by == ADRESS ? node->address : node->uname;
  char *input = node->order_by == ADRESS ? address : uname;
  int cmp_res = strcmp(cmp, input) > 0;
  t_node *next_node = cmp_res ? node->left : node->right;
  t_node *new_node;

  if (next_node != NULL) {
    return node_push(next_node, address, uname);
  }

  new_node = node_init();
  strcpy(new_node->address, address);
  strcpy(new_node->uname, uname);
  new_node->order_by = node->order_by;

  if (cmp) {
    node->left = new_node;
  } else {
    node->right = new_node;
  }
  return 0;
}



void btree_traverse_print(t_node *root) {
  node_print(root);
  if (root->left) {
    btree_traverse_print(root->left);
  }

  

  if (root->right) {
    btree_traverse_print(root->left);
  }

}
