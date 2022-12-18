
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pgm/menu.c"
#include "pgm/reader.c"
#include "pgm/transformer.c"

int main(int argc, char **argv) {
  // const char *path = "assets/kubus.pgm";
  // PGMImage *im = new_pgm(path), *cp1, *cp2;
  // FILE *out = fopen("output/test.pgm", "w");
  // // histogram_equilization(im);
  // gray_range_shift(im, 50, 100);
  // write_to_file(out, im);
  // write_to_file(out, im);
  // fclose(out);

  repl_main_loop();
  return 0;
}
