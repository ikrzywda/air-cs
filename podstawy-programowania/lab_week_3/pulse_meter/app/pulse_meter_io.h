#ifndef PULSE_METER_IO_H
#define PULSE_METER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "constants.h"

float parse_timestamp_v1(char *raw_timestamp) {
  char c, buffer[20];
  int i = 0, mult = 3600;
  float result = 0;

  while ((c = *raw_timestamp++) != '\0') {
    if (c == ':') {
      buffer[i] = '\0';
      result += atof(buffer) * mult;
      mult /= 60;
      i = 0;
    } else {
      buffer[i] = c;
    }
    ++i;
  }
  buffer[i] = '\0';
  result += atof(buffer);
  return result;
}

float parse_timestamp_v2(char *raw_timestamp) {
  char c, buffer[20];
  int i = 0;
  float result = 0;

  while ((c = *raw_timestamp++) != '\0') {
    if (c == '\'') {
      buffer[i] = '\0';
      result = atof(buffer) * 60;
      i = 0;
    } else {
      buffer[i] = c;
    }
    ++i;
  }
  buffer[i] = '\0';
  result += atof(buffer);
  return result;
}

void pretty_print_data_batch(float values[BATCH_LENGTH], int row_length) {
  for (int i = 0; i < BATCH_LENGTH; ++i) {
    printf("%f ", values[i]);
    if (!(i % row_length)) {
      putchar('\n');
    }
  }
}

int scan_data_chunk(float *duration, float pressures[BATCH_LENGTH],
                    float (*parse_timestamp_ptr)(char *)) {
  char time_buffer[20];
  float pressure, start_time, end_time;
  int i = 0;

  for (; i < BATCH_LENGTH && (scanf("%s %f", time_buffer, &pressure) == 2);
       ++i) {
    if (!i) {
      start_time = (*parse_timestamp_ptr)(time_buffer);
    }

    pressures[i] = pressure;
  }
  end_time = (*parse_timestamp_ptr)(time_buffer);
  *duration = end_time - start_time;
  return i;
}

int scan_normalized_data_chunk(int pressures[BATCH_LENGTH]) {
  int pressure, i = 0;
  for (; i < BATCH_LENGTH && (scanf("%d", &pressure) == 2); ++i) {
    if (pressure < INPUT_LOWER_BOUND || pressure > INPUT_UPPER_BOUND) {
      continue;
    }
    pressures[i] = pressure;
  }
  pressures[i] = EXIT_CODE;
  return i;
}

#endif
