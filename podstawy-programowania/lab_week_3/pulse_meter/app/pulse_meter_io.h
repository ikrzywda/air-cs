#ifndef PULSE_METER_IO_H
#define PULSE_METER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

float parse_raw_timestamp(char *raw_timestamp) {
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

void pretty_print_data_batch(float values[BATCH_LENGTH], int row_length) {
  for (int i = 0; i < BATCH_LENGTH; ++i) {
    printf("%f ", values[i]);
    if (!(i % row_length)) {
      putchar('\n');
    }
  }
}

int scan_data_chunk(float times[BATCH_LENGTH], float pressures[BATCH_LENGTH]) {
  char time_buffer[20];
  float pressure;
  int i = 0;
  for (; i < BATCH_LENGTH && (scanf("%s %f", time_buffer, &pressure) == 2);
       ++i) {
    times[i] = parse_raw_timestamp(time_buffer);
    pressures[i] = pressure;
  }
  return i;
}

#endif
