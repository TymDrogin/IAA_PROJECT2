//
// Created by tim on 11/24/24.
//
#include "data.h"

#include <stdlib.h>
#include <stdio.h>

#include "common-defines.h"


Data create_config(const int target_sum_in_cents, int* coin_values_in_cents, const int coin_types_n) {
    Data config =  {
        target_sum_in_cents,
        coin_types_n,
        coin_values_in_cents,
    };
    return config;
}
void free_data(Data* data) {
    free(data->coin_values_in_cents);
    free(data);
}

void print_data(const Data* data) {
    if (data == NULL) {
        fprintf(stderr, "Config is NULL.\n");
        return;
    }
    printf("Config contents:\n");
    printf("Target sum: %d\n", data->target_sum_in_cents);
    printf("Number of coin types: %d\n", data->coin_types_n);
    printf("Coin types:\n");

    for (int i = 0; i < data->coin_types_n; i++) {
        printf("  C%d: %d \n", i + 1, data->coin_values_in_cents[i]);
    }
}
