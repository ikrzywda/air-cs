#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"

#define LINE_BUFFER_LENGTH 100
#define MAX_PATH_LENGTH 100
#define MAX_ARG_COUNT 2
#define COMMAND_COUNT 5
#define ERROR_BUFFER_LENGTH 250

typedef struct Session {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  PGMImage *pgm_image;
  char error_buffer[ERROR_BUFFER_LENGTH];
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
    "load", "save", "invert", "exit", "display",
};


Commands parse_command(char *token);
int init_session(Session *session);
int load_file(Session *session, char *path);
int repl_main_loop();

#endif
