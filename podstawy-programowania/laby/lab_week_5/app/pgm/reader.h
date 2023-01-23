#ifndef READER_H
#define READER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 1024

typedef enum { P2, P3 } PGMType;

typedef struct {
  int width, height, bit_depth, contents_length;
  PGMType file_type;
  int *contents;
} Image;

int read_header(FILE *input_stream, Image *output);
int *load_contents(FILE *input_stream, int length);
int write_to_file(FILE *write_stream, Image *source);

Image *new_image(FILE *input_stream);
Image *ppm_to_pgm(Image *ppm);
void free_pgm(Image *pgm);

#endif
