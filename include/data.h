//
// Created by tim on 11/24/24.
//
#ifndef PROGRAM_CONFIGURATION_H
#define PROGRAM_CONFIGURATION_H

struct Data {
    float target_sum_in_euros;
    int coin_types_n;
    float* coin_values;
};
typedef struct Data Data;

Data create_data(float target_sum_in_euros, float* coin_values, int coin_types_n);
void free_data(Data* data);
void print_data(const Data* data);

#endif //PROGRAM_CONFIGURATION_H
