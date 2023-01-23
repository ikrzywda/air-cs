
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pgm/cli.h"
#include "pgm/reader.h"
#include "pgm/transformer.h"

int main(int argc, char **argv) {

  Session session;
  session.display_flag = 0;
  session.operation_count = 0;

  Operation *operation;
  int c;
  while ((c = getopt(argc, argv, "i:o:dnt:s:e")) != -1) {
    switch (c) {
    case 'i': {
      strcpy(session.source_path, optarg);
      break;
    }
    case 'o': {
      strcpy(session.target_path, optarg);
      break;
    }
    case 'd': {
      session.display_flag = 1;
      break;
    }
    case 'n': {
      session.operations[session.operation_count].transformation = INVERT;
      session.operation_count++;
      break;
    }
    case 't': {
      init_operation(&session.operations[session.operation_count], 1);
      session.operations[session.operation_count].transformation = THRESHOLD;
      strcpy(session.operations[session.operation_count].args[0], optarg);
      session.operation_count++;
      break;
    }
    case 's': {
      init_operation(&session.operations[session.operation_count], 2);
      session.operations[session.operation_count].transformation = SHIFT;
      optind--;
      for (int i = 0; optind < argc && *argv[optind] != '-' && i <= 2;
           optind++) {
        strcpy(session.operations[session.operation_count].args[i++],
               argv[optind]);
      }
      session.operation_count++;
      break;
    }
    case 'e': {
      init_operation(&session.operations[session.operation_count], 1);
      session.operations[session.operation_count].transformation = EQUALIZE;
      strcpy(session.operations[session.operation_count].args[0], optarg);
      session.operation_count++;
      break;
    }
    }
  }

  run_session(&session);

  return 0;
}
