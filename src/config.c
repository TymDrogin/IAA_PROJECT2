//
// Created by tim on 11/24/24.
//
#include "config.h"

#include <stdlib.h>

#include "common-defines.h"


Config create_config(int max_num_of_coins, float target_sum_in_euros, float* coin_values) {
    Config config = {
        max_num_of_coins,
        target_sum_in_euros,
        coin_values,
    };

    return config;
}
void free_config(Config* config) {
    free(config->coin_values);
    free(config);
}
