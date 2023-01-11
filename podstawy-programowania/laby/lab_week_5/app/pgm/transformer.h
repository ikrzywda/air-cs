#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "reader.h"

int invert_image(Image *source);
int histogram_equilization(Image *source);
int gray_range_shift(Image *source, int black_lvl, int white_lvl);
int thresholding(Image *source, int threshold);

#endif
