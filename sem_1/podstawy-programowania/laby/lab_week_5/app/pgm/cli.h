#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "reader.h"
#include "transformer.h"

#define LINE_BUFFER_LENGTH 100
#define MAX_ARG_LENGTH 128
#define MAX_PATH_LENGTH 100
#define MAX_ARG_COUNT 2
#define COMMAND_COUNT 9
#define ERROR_BUFFER_LENGTH 250
#define MAX_OPERATION_COUNT 4

typedef enum {
  INVERT,
  EQUALIZE,
  SHIFT,
  THRESHOLD,
} Transformation;

typedef struct {
  Transformation transformation;
  char *args[MAX_ARG_COUNT];
} Operation;

typedef struct {
  int argc;
  char *const *argv;
  const char *template;
} GetOptArgs;

typedef struct {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  int display_flag;
  int operation_count;
  Image *image;
  Operation operations[MAX_OPERATION_COUNT];
} Session;

int run_session(Session *session);
int init_operation(Operation *operation, int arg_count);

#endif
