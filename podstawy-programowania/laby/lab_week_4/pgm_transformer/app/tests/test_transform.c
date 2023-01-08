#include <assert.h>
#include <stdio.h>

#include "../pgm/reader.c"
#include "../pgm/transformer.c"



#define IMAGE_FIXTURE_WIDTH 5
#define IMAGE_FIXTURE_HEIGHT 51
#define IMAGE_FIXTURE_CONTENT_LENGTH 255
#define IMAGE_FIXTURE_BIT_DEPTH 255

PGMImage *image_fixture(int range_start, int range_end) {
  PGMImage *image_fixture = malloc(sizeof(PGMImage));
  image_fixture->contents = malloc(sizeof(int) * IMAGE_FIXTURE_CONTENT_LENGTH);

  image_fixture->contents_length = IMAGE_FIXTURE_CONTENT_LENGTH;
  image_fixture->width = IMAGE_FIXTURE_WIDTH;
  image_fixture->height = IMAGE_FIXTURE_HEIGHT;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;

  for (int i = range_start; i <= range_end; ++i) {
    image_fixture->contents[i] = i;
  }

  return image_fixture;
}

void test_invert() {
  PGMImage *image = image_fixture(0, IMAGE_FIXTURE_BIT_DEPTH);

  invert_image(image);

  for (int i = 0; i < IMAGE_FIXTURE_CONTENT_LENGTH; ++i) {
    assert(image->contents[i] == IMAGE_FIXTURE_BIT_DEPTH - i);
  }
  printf("TEST INVERT PASSED\n");
}


int main(int argc, char **argv) {
  test_invert();
}
