CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
SRCDIR = app
TARGET = pulse_meter
SOURCES = $(SRCDIR)/app.c

all: compile-debug quick_run

build: compile

format:
	clang-format --style=Google -i $(SRCDIR)/*

compile: $(OBJ)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)

compile-debug: $(OBJ)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET) -D BATCH_LENGTH=${BATCH_LENGTH}

quick_run: 
	./pulse_meter $(flags) < $(input)
