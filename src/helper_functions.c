//
// Created by tim on 11/24/24.
//
#include "helper_functions.h"

#include <stdlib.h>
#include <math.h>

// TODO: ADD ROUND

// Conversion functions
int cents_from_euros(const float euros) {
    return (int)(euros * CENTS_IN_ONE_EURO);
}
float euros_from_cents(const int cents) {
    return (float)cents / (float)CENTS_IN_ONE_EURO;
}

// Solution related
int solution_total_in_cents(const int* solution, const Data* data) {
    int total = 0;
    for (int i = 0; i < data->coin_types_n; i++) {
        total += data->coin_values_in_cents[i] * solution[i];
    }
    return total;
}
int solution_target_diff(const int* solution, const Data* data) {
    return solution_total_in_cents(solution, data) - data->target_sum_in_cents;
}
int num_of_coins_used(const int* solution, const Data* data) {
    int num_of_coins = 0;
    for (int i = 0; i < data->coin_types_n; i++) {
        num_of_coins += solution[i];
    }
    return num_of_coins;
};

bool is_valid_solution(const int* solution, const Data* data) {
    if (solution_total_in_cents(solution, data) != data->target_sum_in_cents) {
        return false;
    }
    return true;
};
