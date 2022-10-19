#include <stdio.h>
#include <string.h>

#include "constants.h"

int **parse_row(char **row) {
    char c;
    char buffer[100];
    int i = 0, temp_min;
    float timestamp = 0, pressure = 0;

    while ((c = row++) != '\n') {
        if (c == '\'') {
            sscanf(buffer, "%d", &temp_min);
            
        }
    }
}

void print_values(int *values, int length, int row_width)
{
    for (int i = 0; i < length; ++i)
    {
        if (!(i % row_width))
        {
            printf("\n");
        }
        printf("%d ", values[i]);
    }
}