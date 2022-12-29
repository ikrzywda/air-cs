#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "reader.h"

int invert_image(PGMImage *source);
int histogram_equilization(PGMImage *source);
int gray_range_shift(PGMImage *source, int black_lvl, int white_lvl);
int thresholding(PGMImage *source, int threshold);

#endif
