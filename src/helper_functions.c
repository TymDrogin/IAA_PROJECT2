//
// Created by tim on 11/24/24.
//
#include "helper_functions.h"

#include <stdlib.h>

bool is_valid_solution(const int* solution, const int* base_coins) {
    if (sizeof(solution) != sizeof(base_coins)) {
        return false;
    }

    int total = 0;
    for (int i = 0; i < COIN_TYPES_NUM; i++) {
        total += base_coins[i] * solution[i];
    }

    if (total == TARGET_SUM) {
        return true;
    } else {
        return false;
    }
};