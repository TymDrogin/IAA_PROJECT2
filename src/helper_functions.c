//
// Created by tim on 11/24/24.
//
#include "helper_functions.h"

#include <stdlib.h>
#include <math.h>


// TODO: ADD ROUND
int get_cents_from_euros(float euros) {
    return (int)(euros * CENTS_IN_ONE_EURO);
}
int get_euros_from_cents(int cents) {
    return (float)cents / (float)CENTS_IN_ONE_EURO;
}


int get_solution_total_in_cents(const int* solution, const int* base_coins, const int coin_types_num) {
    int total = 0;
    for (int i = 0; i < coin_types_num; i++) {
        total += base_coins[i] * solution[i];
    }
    return total;
}
int get_solution_target_diff(const int* solution, const int* base_coins, const int target_in_cents, const int coin_types_num) {
    return get_solution_total_in_cents(solution, base_coins, coin_types_num) - target_in_cents;
}
int get_num_of_coins_used(const int* solution, const int coin_types_num) {
    int num_of_coins = 0;
    for (int i = 0; i < coin_types_num; i++) {
        num_of_coins += solution[i];
    }
    return num_of_coins;
};



bool is_valid_num_of_coins_used(const int* solution, const int max_num_of_coins, const int coin_types_num) {
    return get_num_of_coins_used(solution, coin_types_num) <= max_num_of_coins;
}
bool is_valid_solution(const int* solution, const int* base_coins, const int coin_types_num, const int target_in_cents, const int max_num_of_coins) {
    if (!is_valid_num_of_coins_used(solution, max_num_of_coins, coin_types_num)) {
        return false;
    }

    if (!(get_solution_total_in_cents(solution, base_coins, coin_types_num) == target_in_cents)) {
        return false;
    }

    return true;
};
