
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pgm/menu.c"
#include "pgm/reader.c"
#include "pgm/transformer.c"

int main(int argc, char **argv) {
  repl_main_loop();
  return 0;
}
