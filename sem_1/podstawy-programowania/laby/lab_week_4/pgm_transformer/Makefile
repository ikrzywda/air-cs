
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
BUILD_DIR = build
SRC_DIR = app
SOURCES = $(shell find $(SRC_DIR)/ -name "*.c")
TARGET  = pgm
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

default: $(TARGET)

.SECONDEXPANSION:

$(OBJECTS) : $$(patsubst $(BUILD_DIR)/%.o,$(SRC_DIR)/%.c,$$@)
    	mkdir -p $(@D)
    	$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET): $(OBJECTS)
    	$(CC) -o $@ $(CFLAGS) $^

.PHONY: default
