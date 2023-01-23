CC = gcc
CFLAGS = -Wall
SRCDIR = pgm
BUILD_DIR = build


SOURCES = app.c $(SRCDIR)/cli.c $(SRCDIR)/reader.c \
		  $(SRCDIR)/transformer.c
OBJ = app.o $(SRCDIR)/cli.o $(SRCDIR)/reader.o \
		  $(SRCDIR)/transformer.o

build: $(OBJ)
	gcc -o transformer $(SOURCES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 
