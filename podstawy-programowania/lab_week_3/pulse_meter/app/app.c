#include "constants.h"
#include "pulse_meter.h"
#include "pulse_meter_io.h"

int main(int argc, char **argv) {
  float time[100], pressure[100];
  float bpm;

  while (scan_data_chunk(time, pressure)) {
    bpm = compute_bpm(pressure, 10);
    printf("BPM: %f ", bpm);
    if (bpm < LOWER_BPM_THRESHOLD) {
      printf("[ERROR] BPM too low");
    }
    if (bpm > UPPER_BPM_THRESHOLD) {
      printf("[ERROR] BPM too high");
    }
    putchar('\n');
  }

  return 0;
}
