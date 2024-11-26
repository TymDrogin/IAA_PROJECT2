//
// Created by tim on 11/24/24.
//
#include "data.h"

#include <stdlib.h>
#include <stdio.h>

#include "common-defines.h"


Data create_config(const float target_sum_in_euros, float* coin_values, const int coin_types_n) {
    Data config =  {
        target_sum_in_euros,
        coin_types_n,
        coin_values,
    };
    return config;
}
void free_data(Data* data) {
    free(data->coin_values);
    free(data);
}

void print_data(const Data* data) {
    if (data == NULL) {
        fprintf(stderr, "Config is NULL.\n");
        return;
    }
    printf("Config contents:\n");
    printf("Target sum: %f\n", data->target_sum_in_euros);
    printf("Number of coin types: %d\n", data->coin_types_n);
    printf("Coin types:\n");

    for (int i = 0; i < data->coin_types_n; i++) {
        printf("  C%d: %f\n", i + 1, data->coin_values[i]);
    }
}
