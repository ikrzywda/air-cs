#include <assert.h>
#include <stdlib.h>

#include "../pgm/reader.c"
#include "../pgm/transformer.c"

#define PRINT_SUCCESS() printf("%s...PASSED\n", __func__)
#define DEBUG_INT_PRINT(val) printf("DEBUG: %d\n", val)

#define IMAGE_FIXTURE_WIDTH 5
#define IMAGE_FIXTURE_HEIGHT 51
#define IMAGE_FIXTURE_CONTENT_LENGTH 255
#define IMAGE_FIXTURE_BIT_DEPTH 255

Image *ranged_image_fixture(int range_start, int range_end) {
  int size = range_end - range_start + 1;
  Image *image_fixture = malloc(sizeof(Image));
  image_fixture->contents = malloc(sizeof(int) * size);

  image_fixture->contents_length = size;
  image_fixture->width = IMAGE_FIXTURE_WIDTH;
  image_fixture->height = size / IMAGE_FIXTURE_WIDTH;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;

  for (int i = 0; i < size; ++i) {
    image_fixture->contents[i] = i + range_start;
  }

  return image_fixture;
}

Image *full_range_image_fixture() {
  Image *image_fixture = malloc(sizeof(Image));
  image_fixture->contents = malloc(sizeof(int) * IMAGE_FIXTURE_CONTENT_LENGTH);

  image_fixture->contents_length = IMAGE_FIXTURE_CONTENT_LENGTH;
  image_fixture->width = IMAGE_FIXTURE_WIDTH;
  image_fixture->height = IMAGE_FIXTURE_HEIGHT;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;

  for (int i = 0; i < IMAGE_FIXTURE_CONTENT_LENGTH; ++i) {
    image_fixture->contents[i] = i;
  }

  return image_fixture;
}

Image *single_value_image_fixture(int value) {
  Image *image_fixture = malloc(sizeof(Image));
  image_fixture->contents = malloc(sizeof(int));

  image_fixture->contents[0] = value;
  image_fixture->contents_length = 1;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;
  image_fixture->width = 1;
  image_fixture->height = 1;

  return image_fixture;
}

void test_invert() {
  Image *image = full_range_image_fixture();

  invert_image(image);

  for (int i = 0; i < IMAGE_FIXTURE_CONTENT_LENGTH; ++i) {
    assert(image->contents[i] == IMAGE_FIXTURE_BIT_DEPTH - i);
  }
  PRINT_SUCCESS();
}

void test_gray_range_shift_black_range() {
  Image *image = single_value_image_fixture(10);
  gray_range_shift(image, 20, 200);
  assert(image->contents[0] == 0);

  PRINT_SUCCESS();
}

void test_gray_range_shift_white_range() {
  Image *image = single_value_image_fixture(100);
  gray_range_shift(image, 20, 90);
  assert(image->contents[0] == 90);

  PRINT_SUCCESS();
}

void test_gray_range_shift_mid_value() {
  Image *image = single_value_image_fixture(100);
  int target_value =
      (int)((50 - 10) * (float)(IMAGE_FIXTURE_BIT_DEPTH / (10 * 100)));
  gray_range_shift(image, 10, 100);
  assert(image->contents[0] == target_value);

  PRINT_SUCCESS();
}

void test_histogram_equalization_range_ends() {
  Image *image = ranged_image_fixture(100, 150);

  histogram_equilization(image);
  assert(image->contents[0] == 0);
  assert(image->contents[image->contents_length - 1] ==
         IMAGE_FIXTURE_BIT_DEPTH);

  PRINT_SUCCESS();
}

void test_histogram_equalization_mid_range() {
  Image *image = ranged_image_fixture(0, 2);
  histogram_equilization(image);

  assert(image->contents[1] == IMAGE_FIXTURE_BIT_DEPTH / 2);
  PRINT_SUCCESS();
}

void test_thresholding_below() {
  Image *image = single_value_image_fixture(100);
  thresholding(image, 105);

  assert(image->contents[0] == 0);
  PRINT_SUCCESS();
}

void test_thresholding_above() {
  Image *image = single_value_image_fixture(110);

  thresholding(image, 105);
  assert(image->contents[0] == IMAGE_FIXTURE_BIT_DEPTH);
  PRINT_SUCCESS();
}

int main(int argc, char **argv) {
  test_invert();
  test_gray_range_shift_black_range();
  test_gray_range_shift_white_range();
  test_gray_range_shift_mid_value();
  test_histogram_equalization_range_ends();
  test_histogram_equalization_mid_range();
  test_thresholding_below();
  test_thresholding_above();
}
