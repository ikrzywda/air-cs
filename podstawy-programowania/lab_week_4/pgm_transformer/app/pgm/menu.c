#include "menu.h"
#include "reader.h"
#include "transformer.h"

Commands parse_command(char *token) {
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    if (!strcmp(token, COMMANDS[i])) {
      return i;
    }
  }
  return -1;
}

int load_file(Session *session, char *path) {
    FILE *input_stream = fopen(path, "r");
    if (!input_stream) {
        return 1;
    }

    if (session->pgm_image) {
        free_pgm(session->pgm_image);
        session->pgm_image = NULL;
    }

    session->pgm_image = new_pgm(input_stream);

    strcpy(session->source_path, path);
    session->is_source = 1;
    fclose(input_stream);
    return 0;
}


int save_pgm(Session *session, char *path) {
    FILE *output_stream = fopen(path, "w");
    if (!output_stream || !session->pgm_image) {
        return 1;
    }

    write_to_file(output_stream, session->pgm_image);

    strcpy(session->target_path, path);
    session->is_target = 1;
    fclose(output_stream);
    return 0;
    
}

int init_session(Session *session) {
    
    if (!session) {
        return 1;
    }

    for (int i = 0; i < MAX_ARG_COUNT; ++i) {
        session->args[i] = malloc(MAX_PATH_LENGTH);
    }
    session->is_error = 0;
    session->is_source = 0;
    session->is_target = 0;
    session->pgm_image = NULL;

    return 0;
}


int display(Session *session, char *path) {
    char *target_path = path ? path : session->target_path;
    char display_cmd[LINE_BUFFER_LENGTH];
    FILE *check = fopen(target_path, "r");
    if (!check) {
        return 1;
    }
    fclose(check);
    sprintf(display_cmd, "display %s &", target_path);
    system(display_cmd); 
    return 0;
}

int display_status_line(Session *session) {
    if (session->is_source) {
        printf("(%s) ", session->source_path);
    }
    if (session->is_target) {
        printf("-> (%s) ", session->target_path);
    }
    printf(">>> ");
    return 0;
}

int repl_main_loop() {
  Session session;
  char buffer[LINE_BUFFER_LENGTH];
  char *command_token, *current_token, *args[MAX_ARG_COUNT];
  int arg_i = 0;

  if (init_session(&session)) {
    return 1;
  }

  while (!display_status_line(&session) && fgets(buffer, LINE_BUFFER_LENGTH, stdin)) {
    

    command_token = strtok(buffer, " \n");

    if (command_token == NULL) {
      continue;
    }

    for (arg_i = 0; arg_i < MAX_ARG_COUNT &&
           (current_token = strtok(NULL, " \n")) != NULL;
         ++arg_i) {
        strcpy(session.args[arg_i], current_token);
    }
    session._argc = arg_i;

    switch (parse_command(command_token)) {
      case LOAD_SOURCE_FILE: {
        if (session._argc < 1) {
            strcpy(session.error_buffer, "load file command takes one argument");
            session.is_error = 1;
            break;
        }
        if (load_file(&session, session.args[0])) {
            sprintf(session.error_buffer, "failed to load file: %s", session.args[0]);
            session.is_error = 1;
            break;
        }
        break;
      }
      case DISPLAY: {
        if (display(&session, (!session._argc) ? NULL : session.args[0])) {
            strcpy(session.error_buffer, "failed to display");
            session.is_error = 1;
        }
        break;
      }
      case SAVE_TO_FILE: {
        if (session._argc < 1) {
            strcpy(session.error_buffer, "save file command takes one argument");
            session.is_error = 1;
            break;
        }
        if (save_pgm(&session, session.args[0])) {
            strcpy(session.error_buffer, "save file command takes one argument");
            session.is_error = 1;
            break;
        }
        break;
      }
      case INVERT: {
        if (!session.pgm_image) {
            strcpy(session.error_buffer, "no source loaded");
            session.is_error = 1;
            break;
        }
        invert_image(session.pgm_image);
        break;
      }
      case EXIT: {
        return 0;
      }
      default:
        printf("Unexpected command: %s\n", command_token);
        continue;
    }
    if (session.is_error) {
        printf("ERROR: %s\n", session.error_buffer);
        session.is_error = 0;
    }
  }
  return 0;
}
