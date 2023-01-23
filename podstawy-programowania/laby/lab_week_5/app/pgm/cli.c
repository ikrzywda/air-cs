#include "cli.h"

int init_operation(Operation *operation, int arg_count) {
  if (arg_count > 2) {
    return 1;
  }

  for (int i = 0; i < arg_count; ++i) {
    operation->args[i] = malloc(MAX_ARG_LENGTH);
  }
  return 0;
}

int display(Session *session) {
  char display_cmd[LINE_BUFFER_LENGTH];
  FILE *check = fopen(session->target_path, "r");
  if (!check) {
    return 1;
  }
  fclose(check);
  sprintf(display_cmd, "display %s &", session->target_path);
  system(display_cmd);
  return 0;
}

int save_to_file(Session *session) {
  FILE *output_stream = fopen(session->target_path, "w");
  if (!output_stream || !session->image) {
    return 1;
  }

  write_to_file(output_stream, session->image);
  fclose(output_stream);
  return 0;
}

int run_session(Session *session) {

  FILE *source_image_stream = fopen(session->source_path, "r");
  int arg_1, arg_2;

  if (source_image_stream == NULL) {
    fclose(source_image_stream);
    return 1;
  }

  session->image = new_image(source_image_stream);
  fclose(source_image_stream);
  if (session->image->file_type == P3) {
    session->image = ppm_to_pgm(session->image);
  }

  for (int i = 0; i < session->operation_count; ++i) {
    switch (session->operations[i].transformation) {
    case INVERT: {
      invert_image(session->image);
      break;
    }
    case SHIFT: {
      arg_1 = strtol(session->operations[i].args[0], (char **)NULL, 10);
      arg_2 = strtol(session->operations[i].args[1], (char **)NULL, 10);
      gray_range_shift(session->image, arg_1, arg_2);
      break;
    }
    case EQUALIZE: {
      histogram_equilization(session->image);
      break;
    }
    case THRESHOLD: {
      arg_1 = strtol(session->operations[i].args[0], (char **)NULL, 10);
      thresholding(session->image, arg_1);
      break;
    }
    }
  }

  if (save_to_file(session)) {
    return 1;
  }

  if (session->display_flag) {
    display(session);
  }

  return 0;
}
