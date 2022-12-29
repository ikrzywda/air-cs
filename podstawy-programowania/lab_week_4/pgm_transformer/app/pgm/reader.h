#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 1024

typedef struct {
  int width, height, bit_depth, contents_length;
  int *contents;
} PGMImage;

int read_header(FILE *input_stream, PGMImage *output);
int *load_contents(FILE *input_stream, int length);
int write_to_file(FILE *write_stream, PGMImage *source);

PGMImage *new_pgm(FILE *input_stream);
void free_pgm(PGMImage *pgm);

#endif
