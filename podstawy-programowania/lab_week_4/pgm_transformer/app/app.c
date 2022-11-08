
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pgm/reader.c"
#include "pgm/transformer.c"

int main(int argc, char **argv) {
  const char *path = "assets/Claudia.pgm";
  PGMImage *im = new_pgm(path), *cp1, *cp2;
  FILE *out = fopen("output/test.pgm", "w");
  thresholding(im, 50);
  write_to_file(out, im);
  write_to_file(out, im);
  fclose(out);
  return 0;
}
