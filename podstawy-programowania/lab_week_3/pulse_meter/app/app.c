#include "constants.h"
#include "pulse_meter.h"
#include "pulse_meter_io.h"

void read_normalized_data() {
  int pressures[BATCH_LENGTH], intersection_count;
  while (scan_normalized_data_chunk(pressures)) {
    intersection_count = compute_bpm_normalized_input(pressures);
    printf("frequency: %d\t", intersection_count);
    if (intersection_count < LOWER_THRESHOLD_INTERSECTIONS) {
      printf("[ERROR] frequency too low");
    }
    if (intersection_count > UPPER_THRESHOLD_INTERSECTIONS) {
      printf("[ERROR] frequency too high");
    }
    putchar('\n');
  }
}

void read_raw_data(float (*timestamp_parser)(char *)) {
  float bpm, duration, pressures[100];
  while (scan_data_chunk(&duration, pressures, timestamp_parser)) {
    bpm = compute_bpm(pressures, 10);
    printf("bpm: %f\t", bpm);
    if (bpm < LOWER_THRESHOLD_BPM) {
      printf("[ERROR] bpm too low");
    }
    if (bpm > UPPER_THRESHOLD_BPM) {
      printf("[ERROR] bpm too high");
    }
    putchar('\n');
  }
}

int main(int argc, char **argv) {
  float (*timestamp_parser)(char *) = &parse_timestamp_v1;

  if (argc > 1) {
    if (!strcmp(argv[1], "--timestamp-1")) {
      timestamp_parser = &parse_timestamp_v1;
    } else if (!strcmp(argv[1], "--timestamp-2")) {
      timestamp_parser = &parse_timestamp_v2;
    }
    read_raw_data(timestamp_parser);
  }

  read_normalized_data();

  return 0;
}
