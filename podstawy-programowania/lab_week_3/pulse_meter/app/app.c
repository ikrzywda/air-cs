#include "constants.h"
#include "pulse_meter.h"
#include "pulse_meter_io.h"

int main(int argc, char **argv) {
  float time[100], pressure[100];
  float frequency;

  while (scan_data_chunk(time, pressure, parse_timestamp_v1)) {
    frequency = compute_frequency(pressure, 10);
    printf("frequency: %f ", frequency);
    if (frequency < LOWER_FREQUENCY_THRESHOLD) {
      printf("[ERROR] frequency too low");
    }
    if (frequency > UPPER_FREQUENCY_THRESHOLD) {
      printf("[ERROR] frequency too high");
    }
    putchar('\n');
  }

  return 0;
}
