#include "transformer.h"

#include <stdio.h>
#include <stdlib.h>

int invert_image(PGMImage *source) {
  int new_val;

  for (int i = 0; i < source->contents_length; ++i) {
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

int histogram_equilization(PGMImage *source) {
  int min_val = source->bit_depth, max_val = 0;
  int current_val;
  float coefficient, new_val;

  for (int i = 0; i < source->contents_length; ++i) {
    current_val = source->contents[i];
    if (current_val < min_val) {
      min_val = current_val;
    } else if (current_val > max_val) {
      max_val = current_val;
    }
  }

  coefficient = source->bit_depth / (float)(max_val - min_val);

  for (int i = 0; i < source->contents_length; ++i) {
    current_val = source->contents[i];
    new_val = (current_val - min_val) * coefficient;

    source->contents[i] = (int)new_val;
  }
  return 0;
}

int gray_range_shift(PGMImage *source, int black_lvl, int white_lvl) {
  float mid_coeff = source->bit_depth / (black_lvl * white_lvl);
  int current_val, new_val;

  for (int i = 0; i < source->contents_length; ++i) {
    current_val = source->contents[i];

    if (current_val < black_lvl) {
      new_val = 0;
    } else if (current_val > white_lvl) {
      new_val = white_lvl;
    } else {
      new_val = (int)((current_val - black_lvl) * mid_coeff);
    }
    source->contents[i] = new_val;
  }
  return 0;
}
