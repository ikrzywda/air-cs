#include "reader.h"

#define VALUES_PER_LINE 11

int read_header(FILE *input_stream, Image *output) {
  char buffer[LINE_WIDTH], comment_buffer;
  PGMType file_type;
  int width, height, bit_depth;
  if (fgets(buffer, LINE_WIDTH, input_stream) == NULL) {
    return 1;
  }

  printf("%s", buffer);
  if (!strcmp(buffer, "P2\n")) {
    file_type = P2;
  } else if (!strcmp(buffer, "P3\n")) {
    file_type = P3;
  } else {
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
  output->file_type = file_type;

  printf("%d %d %d %d", height, width, bit_depth, file_type);
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

int write_to_file(FILE *write_stream, Image *source) {
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

Image *new_image(FILE *input_stream) {
  int length, read_length, *contents;
  Image *new_image = malloc(sizeof(Image));

  read_header(input_stream, new_image);

  length = new_image->height * new_image->width;
  read_length = new_image->file_type == P2 ? length : length * 3;
  new_image->contents_length = length;
  contents = load_contents(input_stream, read_length);
  new_image->contents = contents;

  return new_image;
}

Image *ppm_to_pgm(Image *ppm) {
  assert(ppm->file_type == P3);
  
  Image *pgm = malloc(sizeof(Image));
  memcpy(pgm, ppm, sizeof(Image));

  int *pgm_contents = malloc(sizeof(int) * ppm->contents_length);
  int rgb_sum = 0, rgb_mean;

  pgm->contents = pgm_contents;
  pgm->file_type = P2;

  for (int i = 0; i < ppm->contents_length; ++i) {
    for (int j = 0; j < 3; ++j) {
      rgb_sum += ppm->contents[(i * 3) + j];
    }
    pgm_contents[i] = rgb_sum / 3;
    rgb_sum = 0;
  }
  return pgm;
}

void free_pgm(Image *pgm) {
  free(pgm->contents);
  free(pgm);
}
