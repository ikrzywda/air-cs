#include "constants.h"
#include "pulse_meter.h"
#include "pulse_meter_io.h"

void read_normalized_data() {
  int pressures[BATCH_LENGTH];
  while (scan_normalized_data_chunk(pressures)) {
    print_frequency(compute_frequency_normalized_input(pressures));
  }
}

void read_raw_data(float (*timestamp_parser)(char *)) {
  float frequency, duration, pressure[100];
  while (scan_data_chunk(&duration, pressure, timestamp_parser)) {
    frequency = compute_frequency(pressure, 10);
    print_frequency(frequency);
  }
}

int main(int argc, char **argv) {
  int raw_input = (argc > 1) ? !strcmp(argv[1], "--raw") : 0;
  float (*timestamp_parser)(char *) = &parse_timestamp_v1;

  if (argc > 2) {
    if (!strcmp(argv[1], "--timestamp-1")) {
      timestamp_parser = &parse_timestamp_v1;
    } else if (!strcmp(argv[1], "--timestamp-2")) {
      timestamp_parser = &parse_timestamp_v2;
    }
  }

  if (raw_input) {
    read_raw_data(timestamp_parser);
  }

  read_normalized_data();

  return 0;
}
