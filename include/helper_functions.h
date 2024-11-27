//
// Created by tim on 11/24/24.
//

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <math.h>

#include "common-defines.h"
#include <stdbool.h>



int solution_target_diff(const int* solution, const int* base_coins, const int coin_types_num, const int target_in_cents);

bool is_valid_solution(const int* solution, const int* base_coins, const int coin_types_num, const int target_in_cents);


#endif //HELPER_FUNCTIONS_H
