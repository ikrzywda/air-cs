#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"
#include "transformer.h"

#define LINE_BUFFER_LENGTH 100
#define MAX_PATH_LENGTH 100
#define MAX_ARG_COUNT 2
#define COMMAND_COUNT 9
#define ERROR_BUFFER_LENGTH 250

typedef struct {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  PGMImage *pgm_image;
  char error_buffer[ERROR_BUFFER_LENGTH];
  char *args[MAX_ARG_COUNT];
  int _argc;
  int is_source, is_target, is_error;
} Session;



typedef enum Commands {
  LOAD_SOURCE_FILE,
  SAVE_TO_FILE,
  EXIT,
  DISPLAY,
  INVERT,
  EQUALIZE,
  SHIFT,
  THRESHOLD,
  HELP,
} Commands;


const char *COMMANDS[COMMAND_COUNT] = {
    "load", "save",  "exit", "display","invert", "equalize", "shift", "threshold", "help"
};

const char *HELP_PROMPT = "\
  commands:\n\
  * load <filename> - load pgm file\n\
  * save <filename> - save image from current session to file\n\
  * display <filename> || display - display image from session (last saved in case of no path provided) / file\n\
  * invert - apply inversion\n\
  * shift <black lvl> <white lvl> - apply gray range shift\n\
  * equalize - apply histogram equalization\n\
  * threshold <threshold> - apply thresholding\n\
  * exit\n\
";

Commands parse_command(char *token);
int init_session(Session *session);
int display(Session *session, char *path);
int load_file(Session *session, char *path);
int repl_main_loop();

#endif
