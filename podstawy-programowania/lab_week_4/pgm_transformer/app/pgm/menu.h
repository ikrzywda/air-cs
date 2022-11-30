#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_LENGTH 100
#define MAX_PATH_LENGTH 100
#define MAX_ARG_COUNT 2
#define COMMAND_COUNT 5

typedef struct Session {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  char *args[MAX_ARG_COUNT];
  int _argc;
} Session;


typedef enum Commands {
  LOAD_SOURCE_FILE,
  SAVE_TO_FILE,
  INVERT,
  EXIT,
  DISPLAY,
} Commands;

const char *COMMANDS[COMMAND_COUNT] = {
  "load",
  "save",
  "invert",
  "exit",
  "display",
};

#endif
