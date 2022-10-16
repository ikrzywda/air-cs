#!/bin/bash

echo "COMPILING TESTS..."
gcc -std=c99 -pedantic -Wall app/tests.c -lm -o tests

echo "RUNNING TESTS..."
./tests

rm tests