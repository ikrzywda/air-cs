#include "constants.h"
#include "pulse_meter.h"
#include "pulse_meter_io.h"

void read_normalized_data() {
  float pressures[BATCH_LENGTH], frequency;
  int end_of_input_flag = 1;
  do {
    end_of_input_flag = !scan_normalized_data_chunk(pressures);
    frequency = compute_frequency_normalized_input(pressures);
    print_frequency(frequency);
  } while (!end_of_input_flag);
}

void read_raw_data(float (*timestamp_parser)(char *)) {
  float frequency, duration, pressure[100];
  while (scan_data_chunk(&duration, pressure, timestamp_parser)) {
    frequency = compute_frequency(pressure, 10);
    print_frequency(frequency);
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
