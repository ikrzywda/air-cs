CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
SRCDIR = app
TARGET = pulse_meter
SOURCES = $(SRCDIR)/app.c


all: compile quick_run

format:
	clang-format --style=Google -i $(SRCDIR)/*

compile: $(OBJ)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)

quick_run: 
	./pulse_meter $(flags) < $(input)
