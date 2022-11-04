#ifndef PULSE_METER_H
#define PULSE_METER_H

#include <stdio.h>
#include <string.h>

#include "constants.h"

float compute_frequency(float data_batch[BATCH_LENGTH], float duration) {
  int change_count = 0;
  for (int i = 0; i < BATCH_LENGTH; ++i) {
    if (!(data_batch[i - 1] < 0) != !(data_batch[i] < 0)) {
      ++change_count;
    }
  }
  return (change_count / duration) * (60 / duration);
}

float compute_frequency_normalized_input(int data_batch[BATCH_LENGTH]) {
  int change_count = 0;
  for (int i = 0; i < BATCH_LENGTH; ++i) {
    if (!(data_batch[i - 1] < 0) != !(data_batch[i] < 0)) {
      ++change_count;
    }
  }
  return (change_count / NORMALIZED_INPUT_DURATION) * (60 / NORMALIZED_INPUT_DURATION);
}

#endif
