#include "reader.h"

#define VALUES_PER_LINE 11

int read_header(FILE *input_stream, PGMImage *output) {
  char buffer[LINE_WIDTH], comment_buffer;
  int width, height, bit_depth;
  if (fgets(buffer, LINE_WIDTH, input_stream) == NULL && strcmp(buffer, "P2")) {
    return 1;
  }

  while ((comment_buffer = fgetc(input_stream)) == '#' &&
         fgets(buffer, LINE_WIDTH, input_stream))
    ;

  ungetc(comment_buffer, input_stream);

  if (fscanf(input_stream, "%d %d %d", &height, &width, &bit_depth) != 3) {
    return 1;
  }

  output->height = height;
  output->width = width;
  output->bit_depth = bit_depth;

  return 0;
}

int *load_contents(FILE *input_stream, int length) {
  int *contents = malloc(sizeof(int) * length), point;

  if (contents == NULL) {
    return NULL;
  }

  for (int i = 0; i < length; ++i) {
    if (!fscanf(input_stream, "%d ", &point)) {
      free(contents);
      return NULL;
    }
    contents[i] = point;
  }
  return contents;
}

int write_to_file(FILE *write_stream, PGMImage *source) {
  fprintf(write_stream, "P2\n%d %d\n%d\n", source->height, source->width,
          source->bit_depth);
  int length = source->width * source->height;
  for (int i = 0; i < length; ++i) {
    if (!(i % VALUES_PER_LINE)) {
      fputc('\n', write_stream);
    }
    fprintf(write_stream, " %-3d ", source->contents[i]);
  }
  return 0;
}

PGMImage *new_pgm(FILE *input_stream) {
  int length, *contents;
  PGMImage *new_image = malloc(sizeof(PGMImage));

  read_header(input_stream, new_image);

  length = new_image->height * new_image->width;
  new_image->contents_length = length;
  contents = load_contents(input_stream, length);
  new_image->contents = contents;

  return new_image;
}

void free_pgm(PGMImage *pgm) {
  free(pgm->contents);
  free(pgm);
}
