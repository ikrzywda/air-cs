CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
SRCDIR = app
TARGET = pulse_meter
SOURCES = $(SRCDIR)/app.c

all: format compile run

format:
	clang-format --style=Google -i $(SRCDIR)/*

compile: $(OBJ)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)

run: 
	./pulse_meter < assets/przeciecia_zera1.txt
