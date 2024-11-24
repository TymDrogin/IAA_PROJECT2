//
// Created by tim on 11/24/24.
//

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "common-defines.h"
#include <stdbool.h>

int get_solution_total_in_cents(const int* solution, const int* base_coins);
int get_solution_target_diff(const int* solution, const int* base_coins, int target_in_cents);
int get_num_of_coins_used(const int* solution);

bool is_valid_num_of_coins_used(const int* solution, int max_num_of_coins);
bool is_valid_solution(const int* solution, const int* base_coins, int target_in_cents, int max_num_of_coins);



#endif //HELPER_FUNCTIONS_H
