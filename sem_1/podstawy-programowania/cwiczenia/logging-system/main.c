#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bin_tree.h"

// optimization: store ids in array - store references (indeces in btrees)

typedef struct {
  t_node *addr_order_root;
  t_node *uname_order_root
} t_addr_uname_collection;

int add_record(t_addr_uname_collection *collection, char *addr, char *uname) {
  node_push(collection->addr_order_root, addr, uname);
  node_push(collection->uname_order_root, addr, uname);
}

int main() {
  t_node *root = node_init();
  root->address = "dupa123";
  root->uname = "jacek placek";
  root->order_by = UNAME;

  node_push(root, "vatican", "beast2137");
  node_push(root, "la guardia", "ahoy");
  node_push(root, "la guardia", "ajoy");

  btree_traverse_print(root);
}






