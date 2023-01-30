CC = gcc
CFLAGS = -Wall -fsanitize=address
SRCDIR = rpn-calculator
BUILD_DIR = build


APP_SOURCES = app.c $(SRCDIR)/evaluator.c $(SRCDIR)/lexer.c \
		  $(SRCDIR)/parser.c $(SRCDIR)/stack.c $(SRCDIR)/token.c
APP_OBJ = app.o $(SRCDIR)/evaluator.o $(SRCDIR)/lexer.o \
		  $(SRCDIR)/parser.o $(SRCDIR)/stack.o $(SRCDIR)/token.o

TEST_SOURCES = tests.c $(SRCDIR)/evaluator.c $(SRCDIR)/lexer.c \
		  $(SRCDIR)/parser.c $(SRCDIR)/stack.c $(SRCDIR)/token.c
TEST_OBJ = tests.o $(SRCDIR)/evaluator.o $(SRCDIR)/lexer.o \
		  $(SRCDIR)/parser.o $(SRCDIR)/stack.o $(SRCDIR)/token.o

build-app: $(OBJ)
	gcc -o rpn $(APP_SOURCES)

build-tests: ${OBJ}
	gcc -o tests $(TEST_SOURCES)

format:
	clang-format -i $(APP_SOURCES) tests.c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 
