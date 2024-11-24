//
// Created by tim on 11/24/24.
//
#include "helper_functions.h"

#include <stdlib.h>


int get_solution_total_in_cents(const int* solution, const int* base_coins) {
    int total = 0;
    for (int i = 0; i < COIN_TYPES_NUM; i++) {
        total += base_coins[i] * solution[i];
    }
    return total;
}
int get_solution_target_diff(const int* solution, const int* base_coins, int target_in_cents) {
    return get_solution_total_in_cents(solution, base_coins) - target_in_cents;
}
int get_num_of_coins_used(const int* solution) {
    int num_of_coins = 0;
    for (int i = 0; i < COIN_TYPES_NUM; i++) {
        num_of_coins += solution[i];
    }
    return num_of_coins;
};

bool is_valid_num_of_coins_used(const int* solution, int max_num_of_coins) {
    return get_num_of_coins_used(solution) <= max_num_of_coins;
}
bool is_valid_solution(const int* solution, const int* base_coins, int target_in_cents, int max_num_of_coins) {
    if (!is_valid_num_of_coins_used(solution, max_num_of_coins)) {
        return false;
    }

    if (!(get_solution_total_in_cents(solution, base_coins) == target_in_cents)) {
        return false;
    }

    return true;
};
