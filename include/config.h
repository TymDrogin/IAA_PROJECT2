//
// Created by tim on 11/24/24.
//
#ifndef PROGRAM_CONFIGURATION_H
#define PROGRAM_CONFIGURATION_H

struct Config {
    int max_num_of_coins;
    float target_sum_in_euros;
    float* coin_values;
};
typedef struct Config Config;

Config create_config(int max_num_of_coins, float target_sum_in_euros, float* coin_values);
void free_config(Config* config);

#endif //PROGRAM_CONFIGURATION_H
