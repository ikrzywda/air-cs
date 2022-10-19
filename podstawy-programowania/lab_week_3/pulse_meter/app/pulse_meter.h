#include <stdio.h>
#include <string.h>

#include "constants.h"

int compute_edge_values(float *data_batch, float results[2])
{
    float min, max;
    min = max = data_batch[0];
    for (int i = 1; i < BATCH_LENGTH; ++i)
    {
        if (data_batch[i] > max)
        {
            max = data_batch[i];
        }
        if (data_batch[i] < min)
        {
            min = data_batch[i];
        }
    }

    results[0] = min;
    results[1] = max;
}

int normalize_input_data(float *data_batch)
{
    float edge_values[2], input_range; // [min, max]
    compute_edge_values(data_batch, edge_values);
    input_range = edge_values[1] - edge_values[0];
    int normalized;

    for (int i = 0; i < BATCH_LENGTH; ++i)
    {
        normalized = (int)((data_batch[i] - edge_values[0]) / input_range) * NORMALIZATION_RANGE + NORMALIZED_RANGE_MIN;
        data_batch[i] = normalized;
    }
}