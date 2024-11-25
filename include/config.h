//
// Created by tim on 11/24/24.
//
#ifndef PROGRAM_CONFIGURATION_H
#define PROGRAM_CONFIGURATION_H

struct Config {
    float target_sum_in_euros;
    int coin_types_n;
    float* coin_values;
};
typedef struct Config Config;

Config create_config(float target_sum_in_euros, float* coin_values, int coin_types_n);
void free_config(Config* config);
void print_config(const Config* config);

#endif //PROGRAM_CONFIGURATION_H
