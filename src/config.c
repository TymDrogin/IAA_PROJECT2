//
// Created by tim on 11/24/24.
//
#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include "common-defines.h"


Config create_config(const float target_sum_in_euros, float* coin_values, const int coin_types_n) {
    Config config =  {
        target_sum_in_euros,
        coin_types_n,
        coin_values,
    };
    return config;
}
void free_config(Config* config) {
    free(config->coin_values);
    free(config);
}

void print_config(const Config* config) {
    if (config == NULL) {
        fprintf(stderr, "Config is NULL.\n");
        return;
    }
    printf("Config contents:\n");
    printf("Target sum: %f\n", config->target_sum_in_euros);
    printf("Number of coin types: %d\n", config->coin_types_n);
    printf("Coin types:\n");

    for (int i = 0; i < config->coin_types_n; i++) {
        printf("  C%d: %f\n", i + 1, config->coin_values[i]);
    }
}
