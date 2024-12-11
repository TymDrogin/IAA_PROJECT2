//
// Created by tim on 11/24/24.
//
#ifndef PROGRAM_CONFIGURATION_H
#define PROGRAM_CONFIGURATION_H

struct Data {
    int target_sum_in_cents;
    int coin_types_n;
    int* coin_values_in_cents;
};
typedef struct Data Data;

Data create_config(const int target_sum_in_cents, int* coin_values_in_cents, const int coin_types_n);
void free_data(Data* data);
void print_data(const Data* data);

#endif //PROGRAM_CONFIGURATION_H
