#include "transformer.h"

#include <stdio.h>
#include <stdlib.h>

int invert_image(PGMImage *source) {
  int length = source->height * source->width;
  int new_val;

  for (int i = 0; i < length; ++i) {
    new_val = source->bit_depth - source->contents[i];
    source->contents[i] = new_val;
  }
  return 0;
}

int thresholding(PGMImage *source, int threshold) {
  int length = source->height * source->width;
  int new_val;

  for (int i = 0; i < length; ++i) {
    new_val = source->contents[i] < threshold ? 0 : source->bit_depth;
    source->contents[i] = new_val;
  }
  return 0;
}
