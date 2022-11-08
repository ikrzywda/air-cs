#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 1024

typedef struct {
  int width, height, bit_depth;
  int *contents;
} PGMImage;

int read_header(FILE *input_stream, PGMImage *output);
int *load_contents(FILE *input_stream, int length);

PGMImage *new_pgm(const char *path);
