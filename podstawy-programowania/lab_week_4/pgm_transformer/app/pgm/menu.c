#include "menu.h"

Commands parse_command(char *token) {
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    if (!strcmp(token, COMMANDS[i])) {
      return i;
    }
  }
  return -1;
}

int repl_main_loop() {
  Session session;
  char buffer[LINE_BUFFER_LENGTH];
  char *command_token, *current_token, *args[MAX_ARG_COUNT];
  int arg_i = 0;

  while (fgets(buffer, LINE_BUFFER_LENGTH, stdin)) {
    command_token = strtok(buffer, " \n");

    if (command_token == NULL) {
      continue;
    }

    for (; arg_i < MAX_ARG_COUNT &&
           (current_token = strtok(NULL, buffer)) != NULL;
         ++arg_i) {
      session.args[arg_i] = current_token;
    }
    session._argc = arg_i;

    switch (parse_command(command_token)) {
      case LOAD_SOURCE_FILE: {
        printf("LOAD!\n");
        break;
      }
      case SAVE_TO_FILE: {
        printf("SAVE!\n");
        break;
      }
      case INVERT: {
        printf("INVERT!\n");
        break;
      }
      case COMMAND_COUNT: {
        printf("CC!\n");
        break;
      }
      case EXIT: {
        return 0;
      }
      default:
        printf("Unexpected command: %s\n", command_token);
        continue;
    }
  }
  return 0;
}
